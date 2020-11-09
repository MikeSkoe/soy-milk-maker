open Reprocessing;
open State;

type productButton = {
    product: Product.t,
    pos: (int, int),
    size: (int, int),
}

let prducts: list(Product.t) = [Soy, Hazelnut, Almond, Walnut];

let makeProductButton = (index, product) => {
    product,
    pos: (index * 130 + 50, 100),
    size: (55 * 2, 55 * 2),
};

let draw = (env, image, _gameState) =>
    prducts   
        |> List.mapi(makeProductButton)
        |> List.iter(button => {
            let (width, height) = button.size;
            let (x, y) = button.pos;
            let name = Product.string_of_product(button.product);
            let cost = "price: " ++ (Product.price_of_product(button.product) |> string_of_int) ++ "$";

            Draw.pushStyle(env);
            Draw.pushMatrix(env);
            {
                Draw.translate(~x=float_of_int(x), ~y=float_of_int(y), env);
                Draw.noFill(env);
                Draw.stroke(Constants.black, env)

                Image.draw(image, env, Image.Product(button.product));

                Draw.translate(~x=0.0, ~y=(55.0 *. 2.0), env);
                Draw.scale(~x=0.5, ~y=0.5, env);

                Draw.text(~body=name, ~pos=(0, 0), env);
                Draw.translate(~x=0.0, ~y=30.0, env);
                Draw.text(~body=cost, ~pos=(0, 0), env);
            }
            Draw.popMatrix(env);
            Draw.popStyle(env);
        });

let mouseDown = (env, gameState) => {
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
        | [first, ..._] => GameReducer.dispatch(gameState, Buy(first.product))
        | [] => gameState
    };
};

let update = (_env, gameState: State.gameState) => gameState;
