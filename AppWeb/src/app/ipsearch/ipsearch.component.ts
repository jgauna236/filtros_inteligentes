import { Component, OnInit, Output, EventEmitter  } from '@angular/core';
import { SocketService } from '../socket.service';
import { RouterModule, Routes, Router } from '@angular/router';



@Component({
  selector: 'app-ipsearch',
  templateUrl: './ipsearch.component.html',
  styleUrls: ['./ipsearch.component.css'],
})
export class IpsearchComponent implements OnInit {
  private ip: string;
  private mostrar: boolean;

  @Output() estadoEvent = new EventEmitter<string>();

  constructor(private socketService: SocketService)  { }

  ngOnInit() {
    this.ip = '';
  }

  onKeydown() {
    this.socketService.buscarMicro(this.ip);
    this.mostrar = true;
  }

}


