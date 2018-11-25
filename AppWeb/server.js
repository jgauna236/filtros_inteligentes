var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);

  app.get('/', function(req, res){
    res.status(200).send('<h1>Servicios de Filtros Inteligentes</h1>');
  });

  io.on('connection', function(socket){
    console.log('se detecto una conexion');

    socket.on('disconnect', function(){
      console.log('usuario desconectado ');
    });
  });

  io.on('apagado', function(){
    console.log('Se envia al micro la opcion de apagado');
  });

  io.on('filtrado', function(){
    console.log('Se envia al micro la opcion de filtrado');
  });

  io.on('lavado', function(){
    console.log('Se envia al micro la opcion de lavado');
  });

  io.on('enjuague', function(){
    console.log('Se envia al micro la opcion de enjuague');
  });

  io.on('desagote', function(){
    console.log('Se envia al micro la opcion de desagote');
  });

  io.on('ping', function(socket){
    console.log('pingueo');
  });

  app.post('/sensor1', function(req, res){
    let estado = req.query["estado"];
    console.log("Se detecto un cambio en el sensor 1");
    if (estado === 1 ){
      res.statusMessage="Se encendio sensor 1";
    }else if(estado === 0 ){
      res.statusMessage="Se apago sensor 1";
    } 
    res.status(200).end();
  });

  app.post('/sensor2', function(req, res){
    let estado = req.query["estado"];
    console.log("Se detecto un cambio en el sensor 2");
    if (estado === 1 ){
      res.statusMessage="Se encendio sensor 2";
    }else if(estado === 0 ){
      res.statusMessage="Se apago sensor 2";
    } 
    res.status(200).end();
  });

  http.listen(3000, function(){
    console.log('Servidor corriendo en el puerto 3000');
  });