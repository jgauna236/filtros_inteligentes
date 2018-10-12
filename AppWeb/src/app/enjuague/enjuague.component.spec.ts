import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { EnjuagueComponent } from './enjuague.component';

describe('EnjuagueComponent', () => {
  let component: EnjuagueComponent;
  let fixture: ComponentFixture<EnjuagueComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ EnjuagueComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(EnjuagueComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
