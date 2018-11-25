import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { FormsModule } from '@angular/forms';

import { AppComponent } from './app.component';
import { NgbModule } from '@ng-bootstrap/ng-bootstrap';
import { ApagadoComponent } from './apagado/apagado.component';
import { FiltradoComponent } from './filtrado/filtrado.component';
import { LavadoComponent } from './lavado/lavado.component';
import { DesagoteComponent } from './desagote/desagote.component';
import { EnjuagueComponent } from './enjuague/enjuague.component';
import { SocketService } from './socket.service';
import { SocketIoModule, SocketIoConfig } from 'ng6-socket-io';
import { IpsearchComponent } from './ipsearch/ipsearch.component';

const config: SocketIoConfig = { url: 'http://localhost:3000', options: {} };

@NgModule({
  declarations: [
    AppComponent,
    ApagadoComponent,
    FiltradoComponent,
    LavadoComponent,
    DesagoteComponent,
    EnjuagueComponent,
    IpsearchComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    NgbModule.forRoot(),
    SocketIoModule.forRoot(config)
  ],
  providers: [SocketService],
  bootstrap: [AppComponent]
})
export class AppModule { }
