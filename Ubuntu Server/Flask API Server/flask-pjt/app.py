from flask import Flask,jsonify

#app name 설정
app = Flask(__name__)

@app.route("/")
def communicate_test():
    return "Success"

count = 0
@app.route("/json")
def res_json():
	global count 
	count += 1
	return jsonify(
		test="SUCCESS",
		count = count
	)
