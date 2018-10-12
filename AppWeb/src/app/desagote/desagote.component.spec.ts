import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { DesagoteComponent } from './desagote.component';

describe('DesagoteComponent', () => {
  let component: DesagoteComponent;
  let fixture: ComponentFixture<DesagoteComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ DesagoteComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(DesagoteComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
