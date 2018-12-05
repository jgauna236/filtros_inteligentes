import { Component, Input  } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'Filtro Inteligente';
  public estado = 'inicial';

  cambiarEstado(estado: string) {
    this.estado = estado;
    console.log('nuevo estado ' + this.estado);
  }

}
