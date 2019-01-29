import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
  title = 'app';
  spiralObject: Object[] = [
    {"name": 11, "isLocked": false},
    {"name": 21, "isLocked": true},
    {"name": 31, "isLocked": false},
    {"name": 41, "isLocked": true},
    {"name": 51, "isLocked": false},
    {"name": 61, "isLocked": false},
  ];
  defaultSpiralConfig: number[] =
  [11,12,13,14,15,16,17,18,
    21,22,23,24,25,26,27,28,
    31,32,33,34,35,36,37,38,
    41,42,43,44,45,46,47,48,
    51,52,53,54,55,56,57,58,
    61,62,63,64,65,66,67,68
  ];
  spiralInfo: Object[] = [];
  
  ngOnInit(): void {
    const _config: Object[] = [];
    this.spiralObject.forEach(spiral => {  _config.push({"name": spiral['name'], "isLocked": spiral['isLocked'] }) 
  });
  
  const _spiralNames: number[] = _config.map(spiral => { return spiral['name'] });
  
  let asd = this.defaultSpiralConfig.filter(spiral => {
    console.log(_spiralNames.includes(spiral));
    
    if (_spiralNames.includes(spiral)) {
      return spiral;
    };
  });
  
  console.log(_config, asd);    
}
}  