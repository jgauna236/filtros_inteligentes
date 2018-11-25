
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs/Observable';
import { Observer } from 'rxjs/Observer';
import { Operation } from '../../modelo/operation';
import { Event } from '../../modelo/event';

import * as socketIo from 'socket.io-client';

const SERVER_URL = 'http://localhost:3000';

@Injectable()
export class SocketService {
    private socket;

    constructor(private socketService: SocketService) {}

    public initSocket(): void {
        this.socket = socketIo(SERVER_URL);
    }

    public buscarMicro(ip: string): void {
        console.log(ip);
    }

    public realizarOperacion(operation: Operation): void {
        this.socket.emit('operation', operation);
    }

    // public onMessage(): Observable<Message> {
    //     return new Observable<Message>(observer => {
    //         this.socket.on('message', (data: Message) => observer.next(data));
    //     });
    // }

    public onEvent(event: Event): Observable<any> {
        return new Observable<Event>(observer => {
            this.socket.on(event, () => observer.next());
        });
    }
}
