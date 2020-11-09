open Reprocessing;
open Milk;

type milkItem = {
    milkMaker: Milk.milkMaker,
    pos: (int, int),
    size: (int, int),
};

let makeMilkButton = (
    index: int,
    milkMaker: Milk.milkMaker,
): milkItem => {
    milkMaker,
    pos: (index * 140 + 100, 400),
    size: (65 * 2, 82 * 2),
};

let draw = (env, image: Reprocessing.imageT, gameState: State.gameState) => 
    gameState.milkMakers
        |> List.mapi(makeMilkButton)
        |> List.iter(({pos, milkMaker}) => {
            let (x, y) = pos;

            switch milkMaker {
                | Bought(optionalMilk) => {
                    let drawImage = Image.draw(image, env);

                    Draw.pushStyle(env);
                    Draw.pushMatrix(env);
                    {
                        Draw.translate(~x=float_of_int(x), ~y=float_of_int(y), env);
                        drawImage(Image.Maker(Bought));

                        Draw.translate(~x=12. *. 2., ~y=24. *. 2., env);
                        switch optionalMilk {
                            | Some(milk) => {
                                let name = Product.string_of_product(milk.source);
                                let profit = "price: " ++ (Milk.price_of_milk(milk) |> string_of_int) ++ "$";

                                drawImage(Image.Bottle(Milk.state_of_milk(milk)))

                                Draw.scale(~x=0.5, ~y=0.5, env);
                                Draw.translate(~x=-20. *. 2., ~y=82. *. 2.8, env);
                                Draw.text(~body=name, ~pos=(0, 0), env);
                                Draw.translate(~x=0.0, ~y=15. *. 2., env);
                                Draw.text(~body=profit, ~pos=(0, 0), env);
                            }
                            | _ => ()
                        }
                    }
                    Draw.popMatrix(env);
                    Draw.popStyle(env);
                }
                | NotBought => {
                    let drawImage = Image.draw(image, env);

                    Draw.pushStyle(env);
                    Draw.pushMatrix(env);
                    {
                        Draw.translate(~x=float_of_int(x), ~y=float_of_int(y), env);

                        drawImage(Image.Maker(NotBought));
                    }
                    Draw.popMatrix(env);
                    Draw.popStyle(env);
                }
            }
        });

let mouseDown = (env, gameState: State.gameState): State.gameState => {
    let mousePos = Env.mouse(env);
    let clickedProducts = gameState.milkMakers
        |> List.mapi(makeMilkButton)
        |> List.filter(button => 
            Collisions.rect_point(
                ~rectPos=button.pos,
                ~rectSize=button.size,
                ~point=mousePos,
            )
        );

    switch clickedProducts {
        | [first, ..._] => switch first.milkMaker {
            | Bought(Some(milk)) => GameReducer.dispatch(gameState, Sell(milk))
            | NotBought => GameReducer.dispatch(gameState, BuyMilkMaker)
            | _ => gameState
        } 
        | [] => gameState
    };
}

let update = (_env, gameState) =>
    GameReducer.dispatch(gameState, Tick);
