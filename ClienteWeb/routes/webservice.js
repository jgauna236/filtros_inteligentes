var express = require('express');
var router = express.Router();
var estado;

//GET home page
router.get('/', function(req, res, next) {
  res.send('Servicio de Filtros Inteligentes');
});

//verificar estado
router.get('/estado', function(req, res, next) {
  res.send('estado');
});

router.post('/estado/:state', function(req, res, next) {
  estado = req.params.state
});


module.exports = router