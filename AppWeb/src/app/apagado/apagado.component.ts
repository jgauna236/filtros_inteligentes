import { Component, OnInit } from '@angular/core';
import { SocketService } from '../socket.service';
import { Operation } from '../../../modelo/operation';

@Component({
  selector: 'app-apagado',
  templateUrl: './apagado.component.html',
  styleUrls: ['./apagado.component.css']
})
export class ApagadoComponent implements OnInit {

  socket: SocketService;

  constructor() { }

  ngOnInit() {
  }

  filtrar() {
    this.socket.realizarOperacion(Operation.FILTRAR);
  }

  lavar() {
    this.socket.realizarOperacion(Operation.LAVAR);
  }

  desagotar() {
    this.socket.realizarOperacion(Operation.DESAGOTAR);
  }
}
