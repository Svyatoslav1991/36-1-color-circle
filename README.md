Purpose of the task
Repeat work with widgets that were studied in the module.
(Practice the use of widgets that were studied in the module.)

What should be done
Let's collect all the knowledge gained in this module in one program.
To do this, let's create an application that contains a circle in the window that changes its color depending on the position of the slider.
If the slider is set to position 0-33, then the circle is green, if 33-66 it is yellow, then red.
A widget that draws a circle can be made a descendant of QWidget.
Now there is no need to override keyPressEvent, as we did for the button during the lesson.
We just want to draw the widget in a special way; it will not respond to clicks.
We will need three png files that correspond to three circles of different colors (you can draw them yourself in Paint or take ready-made ones in the materials for the lesson).
To position the circle and QSlider vertically, we will need to add these two widgets to a QVBoxLayout (both widgets are located in some parent QWidget, as was the case with the layout managers example).
We recommend setting the window to setFixedSize (200, 250) so that the circle remains a circle.
The minimumSizeHint method can return QSize(100, 100), but the sizeHint method does not need to be overridden.
It will be convenient to have three methods for changing colors.
These will resemble the button raise/lower methods from the red button example. One of them might look like this:
void ColorfulCircle::setYellow() {
    mCurrentCircle = mYellowCircle;
    update();
}
To associate changes in slider values with the color of the circle, you can write a small lambda function.
It will check the range in which the new value falls and set the color corresponding to it, changing the picture to one of three.
An example of such binding and a function header might look like this:
QObject::connect(&slider, &QSlider::valueChanged, [&slider, &circle](int newValue)
{ //Here we check the range and set the color of the circle });
Where circle is your widget.
Note that we are capturing the addresses of the slider and the circle. We also process the new value from the slider by specifying int newValue in the function arguments.
We will check this value to see if it is in the range using if/else.
