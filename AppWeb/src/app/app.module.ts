import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { FormsModule } from '@angular/forms';

import { AppComponent } from './app.component';
import { NgbModule } from '@ng-bootstrap/ng-bootstrap';
import { IpsearchComponent } from './ipsearch/ipsearch.component';
import { SocketService } from './socket.service';
import { AppRoutingModule } from './app-routing.module';
import { RouterModule } from '@angular/router';
import { OpcionesComponent } from './opciones/opciones.component';


@NgModule({
  declarations: [
    AppComponent,
    IpsearchComponent,
    OpcionesComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    NgbModule.forRoot(),
    AppRoutingModule
  ],
  providers: [SocketService, RouterModule],
  bootstrap: [AppComponent]
})
export class AppModule { }
