"""Example showing usage of Python code generator using Tkinter (GUI).

This example uses a little GUI implemented with tkinter from the Python
standard library to demonstrate the use of the Python code generator.

In real projects its recommended to use Python's packaging mechanism to
integrate certain state machine code into other projects. Hence, please make
use of the _bin_ folder if you like to write little example scripts.

(The directory structure of this example follows the tradition of all the other
examples. Therefore this exmaple script is located in a _src_ folder.)

If you have problems with the import statements, compare this file with the
autogenerated _default_runtime.py_ inside the _bin_ folder. To generate this
file, activate `General Feature -> DefaultRuntime` in your SGen file.
"""
# statemachine
from trafficlightctrl.trafficlightctrl_statemachine import TrafficLightCtrl
from trafficlightctrl.timer.sct_timer import Timer

from traffic_scene import TrafficScene

import tkinter as tk

class Callback:
    """State machine uses callback operations (here: _synchronize()_).
    """

    def __init__(self, statemachine, scene):
        self.sm = statemachine
        self.scene = scene
        self.is_btn_exit_pressed = False

    def synchronize(self):
        # car lights
        self.scene.tl_car.set_red(self.sm.sci_trafficlight.red)
        self.scene.tl_car.set_yellow(self.sm.sci_trafficlight.yellow)
        self.scene.tl_car.set_green(self.sm.sci_trafficlight.green)
        # ped lights
        self.scene.tl_ped.set_red(self.sm.sci_pedestrian.red)
        self.scene.tl_ped.set_green(self.sm.sci_pedestrian.green)
        self.scene.tl_ped.set_request(self.sm.sci_pedestrian.request)
        # button actions
        if self.scene.btn_pressed_request():
            self.sm.sci_interface.raise_pedestrianrequest()
        if self.scene.is_btn_onoff_pressed:
            self.sm.sci_interface.raise_onoff()
        if self.scene.is_btn_exit_pressed:
            self.is_btn_exit_pressed = True
        # clear GUI events
        self.scene.clear_events()


class Main:

    def __init__(self):
        self.sm = TrafficLightCtrl()
        self.ti = Timer()
        self.root = tk.Tk() # init GUI
        self.scene = TrafficScene(self.root) # create GUI
        self.cb = Callback(self.sm, self.scene)

    def setup(self):
        self.sm.set_timer(self.ti)
        self.sm.sci_interface.operationCallback = self.cb
        self.sm.init()
        self.sm.enter()

    def run(self):
        while self.root.winfo_exists and not self.cb.is_btn_exit_pressed:
            self.sm.run_cycle()
            self.root.update_idletasks()
            self.root.update()
        self.shutdown()

    def shutdown(self):
        print('State machine shuts down.')
        self.sm.unset_timer()
        self.sm.exit()
        self.root.destroy()
        print('Bye!')

if __name__ == '__main__':
    m = Main()
    m.setup()
    m.run()
