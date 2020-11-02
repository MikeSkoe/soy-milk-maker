open Reprocessing;

type milkItem = {
    milk: State.milk,
    pos: (int, int),
    size: (int, int),
};

let makeMilkButton = (
    index: int,
    milk: State.milk,
) => {
    milk,
    pos: (index * 100 + 100, 400),
    size: (100, 35),
};

let draw = (state: State.t, env) => {
    state.milks
        |> List.mapi(makeMilkButton)
        |> List.iter(({size, pos, milk}) => {
            let (width, height) = size;
            let (x, y) = pos;
            let name = State.string_of_product(milk.source);
            let cost = "cost: " ++ string_of_float(milk.time);
            let profit = "profit: " ++ (State.profit_of_milk(milk) |> string_of_int);

            Draw.pushStyle(env);
            Draw.pushMatrix(env);
            {
                Draw.translate(~x=float_of_int(x), ~y=float_of_int(y), env);
                Draw.noFill(env);
                Draw.stroke(Constants.black, env)
                Draw.rect(~pos=(0, 0), ~width, ~height, env);

                Draw.translate(~x=5.0, ~y=0.0, env);
                Draw.text(~body=name, ~pos=(0, 0), env);

                Draw.scale(~x=0.5, ~y=0.5, env);

                Draw.translate(~x=0.0, ~y=80.0, env);
                Draw.text(~body=cost, ~pos=(0, 0), env);

                Draw.translate(~x=0.0, ~y=40.0, env);
                Draw.text(~body=profit, ~pos=(0, 0), env);
            }
            Draw.popMatrix(env);
            Draw.popStyle(env);
        });

    state;
}

let mouseDown = (state: State.t, env) => {
    let mousePos = Env.mouse(env);
    let clickedProducts
        = state.milks
        |> List.mapi(makeMilkButton)
        |> List.filter(button => 
            Collisions.rect_point(
                ~rectPos=button.pos,
                ~rectSize=button.size,
                ~point=mousePos,
            )
        );
    
    switch clickedProducts {
        | [first, ..._] => Reducer.reducer(state, Sell(first.milk))
        | [] => state
    };
}

let update = (state: State.t, env) =>
    Reducer.reducer(state, Tick);
