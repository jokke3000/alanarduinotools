﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace GbReaper.Classes {
    public class Palette {
        public string mName = null;
        public static readonly Palette DEFAULT_PALETTE = new Palette();

        public Color[] mColors;

        public Palette() : this("default", new Color[] {Color.White, Color.LightGray, Color.DarkGray, Color.Gray}) {
            
        }

        public Palette(string pName, Color[] pColors) {
            this.mColors = pColors;
            this.mName = pName;
        }

        /// <summary>
        /// Finds the closest color in palette using the minimum square method
        /// http://www.codeproject.com/Articles/17044/Find-the-Nearest-Color-with-C-Using-the-Euclidean
        /// </summary>
        /// <param name="pColor"></param>
        /// <returns></returns>
        public Color GetNearestColor(Color pColor) {
            Color nearest_color = Color.Empty;
            double dbl_input_red = Convert.ToDouble(pColor.R);
            double dbl_input_green = Convert.ToDouble(pColor.G);
            double dbl_input_blue = Convert.ToDouble(pColor.B);
            double distance = 500.0;

            double dbl_test_red = Convert.ToDouble(pColor.R);
            double dbl_test_green = Convert.ToDouble(pColor.G);
            double dbl_test_blue = Convert.ToDouble(pColor.B);
            double temp;

            foreach (Color o in this.mColors) {
                // compute the Euclidean distance between the two colors
                // note, that the alpha-component is not used in this example
                dbl_test_red = Math.Pow(Convert.ToDouble(o.R) - dbl_input_red, 2.0);
                dbl_test_green = Math.Pow(Convert.ToDouble(o.G) - dbl_input_green, 2.0);
                dbl_test_blue = Math.Pow(Convert.ToDouble(o.B) - dbl_input_blue, 2.0);
                // it is not necessary to compute the square root
                // it should be sufficient to use:
                // temp = dbl_test_blue + dbl_test_green + dbl_test_red;
                // if you plan to do so, the distance should be initialized by 250000.0
                temp = Math.Sqrt(dbl_test_blue + dbl_test_green + dbl_test_red);
                // explore the result and store the nearest color
                if (temp == 0.0) {
                    // the lowest possible distance is - of course - zero
                    // so I can break the loop (thanks to Willie Deutschmann)
                    // here I could return the input_color itself
                    // but in this example I am using a list with named colors
                    // and I want to return the Name-property too
                    nearest_color = o;
                    break;
                }
                else if (temp < distance) {
                    distance = temp;
                    nearest_color = o;
                }
            }

            return nearest_color;
        }
    }
}
