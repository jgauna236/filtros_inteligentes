import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterModule, Routes } from '@angular/router';
import { AppComponent } from './app.component';
import { IpsearchComponent } from './ipsearch/ipsearch.component';

const appRoutes: Routes = [
  { path: 'home', pathMatch: 'full', component: AppComponent },
  { path: 'ip', pathMatch: 'full', component: IpsearchComponent }
];


@NgModule({
  imports: [
    RouterModule.forRoot(
      appRoutes,
      { enableTracing: true } // <-- debugging purposes only
    )
  ],
  exports: [
    RouterModule
  ]
})
export class AppRoutingModule { }
