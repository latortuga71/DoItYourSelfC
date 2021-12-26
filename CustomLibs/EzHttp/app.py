from flask import Flask,request

app = Flask(__name__)

@app.route("/")
def hello_world():
    print(request.headers)
    return "<p>Hello, World!</p>"



if __name__ == "__main__":
    app.run(host="127.0.0.1",port=80)
