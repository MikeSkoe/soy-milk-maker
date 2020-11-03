open Reprocessing;
open State;

type productButton = {
    product: Product.t,
    pos: (int, int),
    size: (int, int),
}

let prducts: list(Product.t) = [Soy, Nut, Coconut];

let makeProductButton = (
    index: int,
    product: Product.t,
) => {
    product,
    pos: (index * 130 + 100, 100),
    size: (130, 35),
};

let draw = (state, env) => switch state {
    | Menu => state
    | Game(gameState) => {
        prducts   
            |> List.mapi(makeProductButton)
            |> List.iter(button => {
                let (width, height) = button.size;
                let (x, y) = button.pos;
                let name = Product.string_of_product(button.product);
                let cost = "price: " ++ (Product.price_of_product(button.product) |> string_of_int);

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

        Game(gameState);
    }
};

let mouseDown = (state: State.t, env) => {
    let mousePos = Env.mouse(env);
    let clickedProducts
        = prducts   
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
