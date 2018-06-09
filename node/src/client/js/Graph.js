import P5 from 'p5'

// p5 sketch
var p = p5 => {

    let data = [
        { label: 'Push', color: '#FFFFFF', points: [], 'visible': true },
        { label: 'Create', color: '#F1B631', points: [], 'visible': true },
        { label: 'Issues', color: '#C01F33', points: [], 'visible': true },
        { label: 'IssueComment', color: '#F67321', points: [], 'visible': true },
        { label: 'PullRequest', color: '#B5B5B7', points: [], 'visible': true },
        { label: 'PullRequestReviewComment', color: '#677077', points: [], 'visible': true },
        { label: 'Watch', color: '#677077', points: [], 'visible': true },
        { label: 'Delete', color: '#C01F33', points: [], 'visible': true },
        { label: 'Fork', color: '#414250', points: [], 'visible': true },
        { label: 'other', color: '#414250', points: [], 'visible': true }
    ];

    const xSize = 60;
    let isSetuped = false;
    let context = {};

    p5.setup = () => {
        p5.createCanvas(512, 512).parent('Graph');
        p5.pixelDensity(1);
        p5.frameRate(20);

        data.forEach(d => {
            for (let i = 0; i < xSize; i++) {
                d.points.push(0);
            }
        });

        isSetuped = true;
        context = document.getElementsByClassName('p5Canvas')[0].getContext('2d');
    };

    p5.draw = () => {
        // detect 1 min
        if (p5.frameCount % (20 * 60) == 0) {
            data.forEach(d => {
                d.points.push(0);
                d.points.shift();
            });
        }

        //p5.clear();
        context.clearRect(0, 0, p5.width, p5.height);

        p5.noFill();
        data.forEach(d => {

            if (d.visible) {
                p5.stroke(d.color);
                p5.beginShape();

                d.points.forEach((y, x) => {
                    p5.vertex(x * 8, 512 - y * 0.5);
                });

                p5.endShape();
            }

        });

    };

    p5.add = i => {
        if (isSetuped) {
            if (i < 0) data[ data.length-1 ].points[xSize - 1]++;
            else data[i].points[xSize - 1]++;
        }
    }

    p5.setVisible = (i, isVisible) => {
        if (isSetuped) data[i].visible = isVisible;
    }
}

export default class Graph extends P5 {
    constructor() {
        super(p);
    }
};
