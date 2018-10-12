import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { ApagadoComponent } from './apagado.component';

describe('ApagadoComponent', () => {
  let component: ApagadoComponent;
  let fixture: ComponentFixture<ApagadoComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ ApagadoComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(ApagadoComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
