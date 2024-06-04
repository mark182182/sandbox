import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: 'app.component.html',
  styleUrls: ['app.component.scss']
})
export class AppComponent implements OnInit {
  spirals = [
    {
      "capacity": 13,
      "createdAt": "2019-01-23T08:46:24.000+0000",
      "currentQuantity": 0,
      "id": 2,
      "modifiedAt": "2019-01-23T08:46:24.000+0000",
      "name": 12,
      "serpaSpiralId": 12
    }
  ];
  _trays = [
    [11, 12, 13, 14, 15, 16, 17, 18],
    [21, 22, 23, 24, 25, 26, 27, 28],
    [31, 32, 33, 34, 35, 36, 37, 38],
    [41, 42, 43, 44, 45, 46, 47, 48],
    [51, 52, 53, 54, 55, 56, 57, 58],
    [61, 62, 63, 64, 65, 66, 67, 68]
  ];
  mixed_trays: any;

  constructor(
  ) {
  }

  ngOnInit() {
    this.spirals = JSON.parse(localStorage.getItem('spiralsList'));
    this.spirals.sort(function (obj1, obj2) {
      return obj1.name - obj2.name;
    });
    console.log(this.spirals);
    this.setTrays(this._trays);
  }

  getIsOnline(): boolean {
    return JSON.parse(localStorage.getItem('isOnline'));
  }

  setTrays(trays) {
    const _mixed_trays = [];
    const _spirals = this.spirals;
    trays.forEach(function (tray) {
      const _tray = [];
      tray.forEach(function (item) {
        const spiral = _spirals.filter(x => x.serpaSpiralId === item);
        if (spiral.length === 1) {
          spiral[0]['isUsed'] = true;
          spiral[0]['isLocked'] = false;
          _tray.push(spiral[0]);
        } else {
          _tray.push({ serpaSpiralId: item, name: '' + item, isUsed: false, isLocked: true });
        }
      });
      _mixed_trays.push(_tray);
    });
    this.mixed_trays = _mixed_trays;
  }

  setPosition(serpaSpiralId: number) {
    console.log(serpaSpiralId);
  }
}
