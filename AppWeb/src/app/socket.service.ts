
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs/Observable';
import { Observer } from 'rxjs/Observer';
import { Operation } from '../../modelo/operation';
import { Event } from '../../modelo/event';

import * as io from 'socket.io-client';
import { callbackify } from 'util';


@Injectable()
export class SocketService {
    private url = 'http://localhost:3000';
    private socket;
    private response;

    constructor() {
        this.response = '';
        this.socket = io(this.url);
    }

    public  buscarMicro(ip: string): string {
        this.socket.emit('busquedaIP', ip , function(answer) {

            console.log(answer);
            this.response = answer;
            console.log(this.response);
        });
        console.log(this.response);
        return this.response;
    }


    public realizarOperacion(operation: Operation): void {
        this.socket.emit('operation', operation);
    }

    public setEstado(estado: string) {
        this.response = estado;
    }

    public getEstado(): string {
        return this.response;
    }

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
