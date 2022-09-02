import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)


# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///orders.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        # Get symbol and number of shares for purchase
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        # Look up the symbol cost
        price = lookup(symbol)
        # Get cash of user
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        # Check valid entrance of data
        if not symbol:
            return apology("enter valid symbol", 400)
        elif price is None:
            return apology("enter valid symbol", 400)

        try:
            shares = int(shares)
            if shares < 1:
                return apology("enter positive number", 400)
        except ValueError:
            return apology("enter positive number", 400)
        # Check the total cost of shares
        shares_price = shares * price["price"]
        # Check if user has enough cash for desired shares
        if shares_price > user_cash:
            return apology("not sufficient cash", 400)
        # Extract cash from user account and update existing stocks data
        else:
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", shares_price, session["user_id"])
            db.execute("INSERT INTO stocks (user_id, symbol, shares, price, operation) VALUES (?, ?, ?, ?, ?)",
                       session["user_id"], symbol.upper(), shares, price["price"], "purchase")

        flash("Purchase successful!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    # Get list stocks wiht date and type of transactions
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?", session["user_id"])
    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    if request.method == "POST":
        # Get user input for new password
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        # Entrance validity check
        if not password:
            return apology("password is missing", 400)
        if not confirmation:
            return apology("password confirmation is missing", 400)
        if not password == confirmation:
            return apology("passwords do not match", 400)
        # Hash and update hash value of user
        else:
            hashed = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
            db.execute("UPDATE users SET hash = ? WHERE id = ?", hashed, session["user_id"])

            flash("Password changed!")
            return redirect("/")

    else:
        return render_template("password.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        # Get user input and look up the value
        quote = lookup(request.form.get("symbol").upper())
        # Entrance validity check
        if quote is None:
            return apology("enter valid symbol", 400)
        # Get data from lookup
        else:
            return render_template("quoted.html", name=quote["name"], symbol=quote["symbol"], price=quote["price"])

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        # Get user input: username & password
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        # Entrance validity check and duplicate elimination
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if not username:
            return apology("username is missing", 400)
        if len(rows) > 0:
            return apology("username already exists, enter another", 400)
        if not password:
            return apology("password is missing", 400)
        if not confirmation:
            return apology("password confirmation is missing", 400)
        if not password == confirmation:
            return apology("passwords do not match", 400)
        # Hash password and create user data
        else:
            hashed = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashed)
            return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        # Get userinput for symbol and number of shares
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        # Entrance validity check
        try:
            shares = int(shares)
            if shares < 1:
                return apology("enter positive number")
        except ValueError:
            return apology("enter positive number")
        if not symbol:
            return apology("enter valid symbol")
        # Get number of shares from user accound
        stocks = db.execute("SELECT SUM(shares) as shares FROM stocks WHERE symbol = ? AND user_id = ?",
                            symbol, session["user_id"])[0]
        # Check if shares are enough
        if shares > stocks["shares"]:
            return apology("not enough shares")
        # Get the price for shares
        price = lookup(symbol)["price"]
        # Get total cost for shares
        total_cost = price * shares
        # Update transaction by decrementing number of shares
        db.execute("INSERT INTO stocks (user_id, symbol, shares, price, operation) VALUES (?, ?, ?, ? , ?)",
                   session["user_id"], symbol, -shares, price, "sale")
        # Increment user cash by cost of sold shares
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_cost, session["user_id"])

        flash("Sale successful!")
        return redirect("/")

    else:
        stocks = db.execute("SELECT symbol FROM stocks WHERE user_id = ? GROUP BY symbol", session["user_id"])
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
