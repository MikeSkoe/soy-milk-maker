open Reprocessing;
open State;

type productButton = {
    product: State.product,
    pos: (int, int),
    size: (int, int),
}

let makeProductButton = (
    index: int,
    product: State.product,
) => {
    product,
    pos: (index * 130 + 100, 100),
    size: (130, 35),
};

let draw = (state, env) => {
    [Soy, Nut, Coconut]
        |> List.mapi(makeProductButton)
        |> List.iter(button => {
            let (width, height) = button.size;
            let (x, y) = button.pos;
            let name = string_of_product(button.product);
            let cost = "price: " ++ (price_of_product(button.product) |> string_of_int);

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
            }
            Draw.popMatrix(env);
            Draw.popStyle(env);
        });

    state;
}

let mouseDown = (state: State.t, env) => {
    let mousePos = Env.mouse(env);
    let clickedProducts
        = [Soy, Nut, Coconut]
        |> List.mapi(makeProductButton)
        |> List.filter(button => 
            Collisions.rect_point(
                ~rectPos=button.pos,
                ~rectSize=button.size,
                ~point=mousePos,
            )
        );
    
    switch clickedProducts {
        | [first, ..._] => Reducer.reducer(state, Buy(first.product))
        | [] => state
    };
};

let update = (state: State.t, env) => {
    state
};
