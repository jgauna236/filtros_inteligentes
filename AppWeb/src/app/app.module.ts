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
import { IpsearchComponent } from './ipsearch/ipsearch.component';
import { SocketService } from './socket.service';
import { AppRoutingModule } from './app-routing.module';



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
    AppRoutingModule
  ],
  providers: [SocketService],
  bootstrap: [AppComponent]
})
export class AppModule { }
