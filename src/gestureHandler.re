open BsReactNative;

type coordinates = {
  x: float,
  y: float,
};

type state = {
  pan: Animated.ValueXY.t,
  childCoordinates: ref(Animated.ValueXY.jsValue),
  panResponder: PanResponder.t,
};

type gestureTypes =
  | Corner(coordinates)
  | TopBottom(float)
  | LeftRight(float)
  | TouchMovement;

let handleRelease = () => ();

let component = ReasonReact.reducerComponent("GestureHandler");

/* ...children needs spread operator because Reason parses the jsx
   'children' and that translates to ([|childred|])   */

let make = children => {
  ...component,
  initialState: () => {
    let pan = Animated.ValueXY.create(~x=0., ~y=0.);
    let childCoordinates = ref({"x": 0., "y": 0.});

    /* PanResponder.() is prefixing contents */
    {
      pan,
      panResponder:
        PanResponder.(
          create(
            ~onStartShouldSetPanResponder=callback((_e, _g) => true),
            ~onPanResponderMove=`update([`XY(pan)]),
            ~onPanResponderRelease=callback((_e, _g) => handleRelease()),
            (),
          )
        ),
      childCoordinates,
    };
  },
  reducer: ((), _state: state) => ReasonReact.NoUpdate,
  render: ({state}) =>
    <View responderHandlers={PanResponder.panHandlers(state.panResponder)}>
      <Animated.View
        style=Style.(
          style([
            Transform.makeAnimated(
              ~translateX=Animated.ValueXY.getX(state.pan),
              ~translateY=Animated.ValueXY.getY(state.pan),
              (),
            ),
            position(Absolute),
          ])
        )>
        ...children
      </Animated.View>
    </View>,
};