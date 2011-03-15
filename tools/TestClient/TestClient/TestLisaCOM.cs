using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows;
using System.Runtime.InteropServices;


namespace TestClient
{
    class TestLisaCOM
    {
        private string method;

        public TestLisaCOM(MainWindow.callbackType callback, Lisa50Lib.ILisaCOM lisa, string method, int step, ushort i, string name)
        {

            this.method = method;

            try
            {

                float t = 0;

                while (true)
                {
                    // remain in the loop while thread is not aborted
                    StringBuilder sb = new StringBuilder();
                    sb.Append(t.ToString()).Append(": ");

                    sb.Append(testMethod(lisa, i, name));

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

        
        private string testMethod(Lisa50Lib.ILisaCOM lisa, ushort i, string name)
        {
            switch (method)
            {
                case "getCOPForce":
                    return testGetCOPForce(lisa);
                case "getCOPPosition":
                    return testGetCOPPosition(lisa);
                case "getJointCoordinates":
                    return testGetJointCoordinates(lisa,i);
                case "getLinkMass":
                    return testGetLinkMass(lisa,i);
                case "getLinkPosition":
                    return testGetLinkPosition(lisa, i);
                case "getLinkPositionByName":
                    return testGetLinkPositionByName(lisa,name);
                default:
                    throw new Exception("Method NOT defined");
            }            
            
        }

        private string testGetLinkPositionByName(Lisa50Lib.ILisaCOM lisa, string name)
        {
            double[] d=lisa.getLinkPositionByName(name);
            return String.Join(", ", d.Select(p => p.ToString()).ToArray());
        }

        private string testGetLinkMass(Lisa50Lib.ILisaCOM lisa, ushort i)
        {
            double d = lisa.getLinkMass(i);
            return d.ToString();
        }

        private string testGetJointCoordinates(Lisa50Lib.ILisaCOM lisa, ushort i)
        {
            double[] d = lisa.getJointCoordinates(i);
            return String.Join(", ", d.Select(p => p.ToString()).ToArray());
        }     

        private static String testGetLinkPosition(Lisa50Lib.ILisaCOM lisa, ushort i)
        {
            double[] d = lisa.getLinkPosition(i);
            return String.Join(", ", d.Select(p => p.ToString()).ToArray());
        }

        private string testGetCOPForce(Lisa50Lib.ILisaCOM lisa)
        {
            double[] d = lisa.getCOPForce();
            return String.Join(", ", d.Select(p => p.ToString()).ToArray());
        }

        private string testGetCOPPosition(Lisa50Lib.ILisaCOM lisa)
        {
            double[] d = lisa.getCOPPosition();
            return String.Join(", ", d.Select(p => p.ToString()).ToArray());
        }

    }
}
