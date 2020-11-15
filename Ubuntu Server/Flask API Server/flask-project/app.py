from flask import Flask

#app name 설정
app = Flask(__name__)

@app.route("/")
def communicate_test():
    return "Success"

