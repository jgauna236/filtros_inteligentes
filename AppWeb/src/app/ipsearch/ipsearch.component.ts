import { Component, OnInit } from '@angular/core';
import { SocketService } from '../socket.service';


@Component({
  selector: 'app-ipsearch',
  templateUrl: './ipsearch.component.html',
  styleUrls: ['./ipsearch.component.css']
})
export class IpsearchComponent implements OnInit {
  private socket: SocketService;
  private ip: string;
  constructor() { }

  ngOnInit() {
    this.ip = '';
  }

  onKeydown() {
    this.socket.buscarMicro(this.ip);
  }

}


