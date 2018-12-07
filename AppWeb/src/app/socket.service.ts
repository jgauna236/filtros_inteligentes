
import { Injectable, OnInit, EventEmitter, Output } from '@angular/core';
import { Observable } from 'rxjs/Observable';
import { Observer } from 'rxjs/Observer';
import { Operation } from '../../modelo/operation';
import { Event } from '../../modelo/event';
import { Router } from '@angular/router';

import * as io from 'socket.io-client';



@Injectable()
export class SocketService {
    private url = 'http://localhost:3000';
    private socket;
    private response;
    private router: Router;

    constructor(  ) {
        this.socket = io(this.url);
    }


    public  buscarMicro(ip: string): void {
        this.socket.emit('busquedaIP', ip , function(answer) {
        });

    }
    public filtrar() {
        console.log('llego');
        this.socket.emit('filtrado');
        this.socket.emit('apagado');

    }

    public lavar() {
        this.socket.emit('lavado');

    }

    public apagar() {

        this.socket.emit('apagado');

    }

    public enjuagar() {

        this.socket.emit('enjuague');

    }

    public desagote() {

        this.socket.emit('desagote');

    }

    public completo() {
        this.socket.emit('apagado');
        this.socket.emit('lavado');
        this.socket.emit('apagado');
        this.socket.emit('enjuague');
        this.socket.emit('apagado');
        this.socket.emit('filtrado');
        this.socket.emit('apagado');
        this.socket.emit('desagote');
        this.socket.emit('apagado');

    }


    public realizarOperacion(operation: Operation): void {
        this.socket.emit('operation', operation);
    }

    // public setEstado(estado: string) {
    //     this.response = estado;
    // }

    // public getEstado(): string {
    //     return this.response;
    // }

    // public onMessage(): Observable<Message> {
    //     return new Observable<Message>(observer => {
    //         this.socket.on('message', (data: Message) => observer.next(data));
    //     });
    // }

    // public onEvent(event: Event): Observable<any> {
    //     return new Observable<Event>(observer => {
    //         this.socket.on(event, () => observer.next());
    //     });
    // }
}
