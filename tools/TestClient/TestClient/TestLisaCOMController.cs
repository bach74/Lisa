using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.InteropServices;

namespace TestClient
{
    class TestLisaCOMController
    {
        public TestLisaCOMController(MainWindow.callbackType callback, Lisa50Lib.ILisaCOMController lisa, string method, int step, ushort i, string name)
        {
            try
            {
                float t = 0;

                while (true)
                {
                    // remain in the loop while thread is not aborted
                    StringBuilder sb = new StringBuilder();
                    sb.Append(t.ToString()).Append(": ");

                    sb.Append(testMethod(lisa, i, method));

                    sb.Append("\n");

                    callback(sb.ToString());

                    // wait some ms before the next call
                    Thread.Sleep(step);
                    t += step / 1000.0f;

                }
            }
            catch (COMException ex)
            {
                // server cause an exception 
                // probably was terminated before this client
                // or API exception was raised
                string msg = ex.Message;
                string st = ex.StackTrace;
            }
            catch (Exception ex)
            {
                string msg = ex.Message;
            }
        }


        private string testMethod(Lisa50Lib.ILisaCOMController lisa, ushort i, string name)
        {
            switch (name)
            {
                case "getParameters":
                    return testGetParameters(lisa, i);
                case "getPosition":
                    return testGetPosition(lisa, i);
                case "getSetpoint":
                    return testGetSetpoint(lisa, i);
                case "getTorque":
                    return testGetTorque(lisa, i);
                case "getVelocity":
                    return testGetVelocity(lisa, i);
                default:
                    throw new Exception("Method NOT defined");
            }

        }

        private string testGetVelocity(Lisa50Lib.ILisaCOMController lisa, ushort i)
        {
            return lisa.getVelocity(i).ToString();
        }

        private string testGetTorque(Lisa50Lib.ILisaCOMController lisa, ushort i)
        {
            return lisa.getTorque(i).ToString();
        }

        private string testGetSetpoint(Lisa50Lib.ILisaCOMController lisa, ushort i)
        {
            return lisa.getSetpoint(i,0).ToString();
        }

        private string testGetPosition(Lisa50Lib.ILisaCOMController lisa, ushort i)
        {
            return lisa.getPosition(i).ToString();
        }

        private string testGetParameters(Lisa50Lib.ILisaCOMController lisa, ushort i)
        {
            double[] d = lisa.getParameters(i);
            return String.Join(", ", d.Select(p => p.ToString()).ToArray());
        }

    }
}
