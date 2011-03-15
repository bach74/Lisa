using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TestClient
{
    /// <summary>
    /// Class to pass threading parameters
    /// </summary>
    public class ThreadParamsTestCOM
    {
        private string method;
        private ushort num;
        private string name;

        public ThreadParamsTestCOM(string method, ushort num, string name)
        {
            this.method = method;
            this.num = num;
            this.name = name;
        }

        public string Method
        {
            get { return method; }
            set { method = value; }
        }

        public ushort Num
        {
            get { return num; }
            set { num = value; }
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }
    }
}
