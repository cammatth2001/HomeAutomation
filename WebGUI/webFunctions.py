from flask import Flask, render_template

app = Flask(__name__)




@app.route('/')
def index():
    return render_template("index.html")

#def homePage():
#    return '<center>Welcome to the homepage of your Automated Services</center>'

#@app.route('/toggleOne')

#def relayPressOne():
#    return '<center>The light has been turned on</center> '

if __name__ == '__main__':
    app.run()



