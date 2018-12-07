import { Component, OnInit } from '@angular/core';
import { SocketService } from '../socket.service';

@Component({
  selector: 'app-opciones',
  templateUrl: './opciones.component.html',
  styleUrls: ['./opciones.component.css']
})
export class OpcionesComponent implements OnInit {

  ngOnInit() {
  }

  constructor(private socketService: SocketService) { }

  filtrar() {
    console.log('llega');
    this.socketService.filtrar();
  }

  lavar() {
    this.socketService.lavar();
  }

  apagar() {
    this.socketService.apagar();
  }

  enjuagar() {
    this.socketService.enjuagar();
  }

  desagote() {
    this.socketService.desagote();
  }

  completo() {
    this.socketService.completo();
  }

}
