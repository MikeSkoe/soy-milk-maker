let line_dot = (~line: (int, int), ~dot: int) => {
    let (min, max) = line;

    dot > min && dot < max
};

let rect_point = (
    ~rectPos: (int, int),
    ~rectSize: (int, int),
    ~point: (int, int),
) => {
    let (x, y) = rectPos;
    let (w, h) = rectSize;
    let (px, py) = point;

    switch (
        line_dot(~line=(x, x + w), ~dot=px),
        line_dot(~line=(y, y + h), ~dot=py),
    ) {
        | (true, true) => true
        | (_, _) => false
    };
}
