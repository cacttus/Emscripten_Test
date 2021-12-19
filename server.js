var express = require('express'),
  bodyParser = require('body-parser'),
  app = express(),
  port = process.env.PORT || 8080;
 
// enable CORS using npm package
//var cors = require(‘cors’);
//app.use(cors());
 app.use(function (req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  //**Uncommenting these will enable SharedArrayBuffer and remove the error in Firefox.
      //res.header("Cross-Origin-Embedder-Policy", "require-corp");
      //res.header("Cross-Origin-Opener-Policy", "same-origin");
  res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  next();
});

// parse application/json
app.use(bodyParser.json());
// parse application/x-www-form-urlencoded
app.use(bodyParser.urlencoded({ extended: true }));


// request handlers
app.get('/', (req, res) => {
//res.render apparently for just non-html
  console.log(req.url);
  res.sendfile('./build/hello.html');
});
app.get('./mario.png', (req, res) => {
//res.render apparently for just non-html
  console.log(req.url);
  res.sendfile('./build/mario.png');
});
 app.get('/hello.js', (req, res) => {
  console.log(req.url);
  res.sendfile('./build/hello.js');
});
 app.get('/hello.wasm', (req, res) => {
  console.log(req.url);
  res.sendfile('./build/hello.wasm');
});
app.get('/build/hello.wasm.map', (req, res) => {
  console.log(req.url);
  res.sendfile('./build/hello.wasm.map');
  });
 app.get('/hello.worker.js', (req, res) => {
  console.log(req.url);
  res.sendfile('./build/hello.worker.js');
});
app.get('/hello.data', (req, res) => {
  console.log(req.url);
  res.sendfile('./build/hello.data');
  });
app.get('*', (req, res) => {
  //res.render apparently for just non-html
  console.log("RESOURCE NOT HANDLED: ");
  console.log(req.url);
});
app.listen(port, () => {
  console.log('Server started on: ' + port);
});
