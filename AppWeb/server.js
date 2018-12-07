var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var ip;
var XMLHttpRequest = require("xmlhttprequest").XMLHttpRequest;
var httpreq = new XMLHttpRequest();

const delay = require('wait-sync');


  app.get('/', function(req, res){
    res.status(200).send('<h1>Servicios de Filtros Inteligentes</h1>');
  });


  io.on('connection', (socket)=>{
    console.log('se detecto una conexion');

    var send= (param)=>{
      httpreq.open("GET", 'http://'+ip+'/'+param,false);
      httpreq.send(null);
      if (httpreq.status != 200) return '';
      return httpreq.responseText;
    }


    
    socket.on('busquedaIP', (ipParam, answer)=>{
      ip = ipParam;
      console.log('busqueda de micro con ip '+ ip);
      var res = send('ping');
      console.log('estado: '+res);
      answer(res.toString());

    });
    
    socket.on('apagado', function(){
      console.log('Se envia al micro ' + ip + ' la opcion de apagado');
      send('stop');
    });
  
    socket.on('filtrado', function(){
      console.log('Se envia al micro ' + ip + ' la opcion de filtrado');
      send('filter');
      delay(3);
    });
  
    socket.on('lavado', function(){
      console.log('Se envia al micro ' + ip + ' la opcion de lavado');
      send('wash');
      delay(3);

    });
  
    socket.on('enjuague', function(){
      console.log('Se envia al micro ' + ip + ' la opcion de enjuague');
      send('rinse');
      delay(3);

    });
  
    socket.on('desagote', function(){
      console.log('Se envia al micro ' + ip + ' la opcion de desagote');
      send('drain');
      delay(3);

    });
  
    socket.on('ping', function(socket){
      console.log('pingueo');
    });
  

  

    socket.on('disconnect', function(){
      console.log('usuario desconectado ');
    });
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

  io.on('ping', ()=>{
    console.log('pingueo');
  });

  http.listen(3000, function(){
    console.log('Servidor corriendo en el puerto 3000');
  });