var express = require('express'),
  bodyParser = require('body-parser'),
  path = require('path'),
  app = express(),
  port = process.env.PORT || 8080;

// enable CORS using npm package
//var cors = require(‘cors’);
//app.use(cors());
app.use(function (req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");

  //Changed this due to 403 when accessing emscripten api locally.
  //res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  res.header('Access-Control-Allow-Headers', 'Content-Type, Authorization, Content-Length, X-Requested-With');
  res.header('Access-Control-Allow-Methods', 'GET, PUT, POST, DELETE, OPTIONS');
  
  //**Uncommenting these will enable SharedArrayBuffer and remove the error in Firefox.
  //res.header("Cross-Origin-Embedder-Policy", "require-corp");
  //res.header("Cross-Origin-Opener-Policy", "same-origin");
  
  next();
});

// parse application/json
app.use(bodyParser.json());
// parse application/x-www-form-urlencoded
app.use(bodyParser.urlencoded({ extended: true }));

// request handlers
app.get('/', (req, res) => {
  //res.render apparently for just non-html
  console.log('->' + req.url);
  res.sendfile('./build/test.html');
});
app.get(/^\/emsdk\/.*$/, (req, res) => {
  console.log('->' + req.url + "  > " + __dirname);
  console.log("->>> " + '..' + req.url, {root : __dirname})
  res.sendFile(req.url, {root : __dirname});
});
app.get(/^\/build\/.*$/, (req, res) => {
  console.log('->' + req.url);
  res.sendfile('.'+req.url);
});
app.get(/^\/.*\.(js|png|wasm|wasm\.map|data)$/, (req, res) => {
  //res.render apparently for just non-html
  console.log('->' + req.url);
  res.sendfile('./build' + req.url);
});
app.get(/^\/.*\.(h|cpp)$/, (req, res) => {
  //res.render apparently for just non-html
  console.log('->' + req.url);
  res.sendfile('.' + req.url);
});
app.get(/^\/.*\.png$/, (req, res) => {
  //res.render apparently for just non-html
  console.log('->' + req.url);
  res.sendfile('./build' + req.url);
});
app.get(/^\/favicon.ico$/, (req, res) => {
  console.log('->' + "No favicon.");
});
app.get('*', (req, res) => {
  //res.render apparently for just non-html
  console.log('->' + "RESOURCE NOT HANDLED: ");
  console.log(req.url);
});
app.listen(port, () => {
  console.log('Server started on: ' + port);
});
