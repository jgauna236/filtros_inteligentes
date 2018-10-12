import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppComponent } from './app.component';
import {NgbModule} from '@ng-bootstrap/ng-bootstrap';
import { ApagadoComponent } from './apagado/apagado.component';
import { FiltradoComponent } from './filtrado/filtrado.component';
import { LavadoComponent } from './lavado/lavado.component';
import { DesagoteComponent } from './desagote/desagote.component';
import { EnjuagueComponent } from './enjuague/enjuague.component';

@NgModule({
  declarations: [
    AppComponent,
    ApagadoComponent,
    FiltradoComponent,
    LavadoComponent,
    DesagoteComponent,
    EnjuagueComponent
  ],
  imports: [
    BrowserModule,
    NgbModule.forRoot()
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
