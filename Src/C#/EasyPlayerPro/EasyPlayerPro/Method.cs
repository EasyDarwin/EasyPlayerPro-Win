using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using System.Net.Security;
using System.Security.Cryptography.X509Certificates;
using System.Net;
using System.IO;
using System.IO.Compression;
using System.Text.RegularExpressions;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Web;
using System.Net.Security;
using System.Security.Authentication;

namespace PlayerSDK
{
   public class Method
    {
        [DllImport("Kernel32.dll")]
        private static extern void GetLocalTime(ref SystemTime lpSystemTime);
         
        [DllImport("Kernel32.dll")]
        private static extern bool SetLocalTime(ref SystemTime lpSystemTime);
         
        [DllImport("Kernel32.dll")]
        private static extern void GetSystemTime(ref SystemTime lpSystemTime);
         
        [DllImport("Kernel32.dll")]
        private static extern bool SetSystemTime(ref SystemTime lpSystemTime);

        public static string WebRequestPost(string url, string data)
        {
            try
            {
                //======================防止基础连接已经关闭: 未能为 SSL/TLS 安全通道建立信任关系
                ServicePointManager.ServerCertificateValidationCallback += RemoteCertificateValidate;
                //========================
                byte[] postBytes = Encoding.GetEncoding("utf-8").GetBytes(data);
                HttpWebRequest myRequest = (HttpWebRequest)WebRequest.Create(url);
                myRequest.Method = "POST";
                //myRequest.ContentType = "application/x-www-form-urlencoded";
                myRequest.ContentType = "application/json";
                myRequest.ContentLength = postBytes.Length;
                myRequest.Proxy = null;
                Stream newStream = myRequest.GetRequestStream();
                newStream.Write(postBytes, 0, postBytes.Length);
                newStream.Close();
                HttpWebResponse myResponse = (HttpWebResponse)myRequest.GetResponse();
                using (StreamReader reader = new StreamReader(myResponse.GetResponseStream(), Encoding.GetEncoding("utf-8")))
                {
                    string content = reader.ReadToEnd();
                    return content;
                }
            }
            catch (System.Exception ex)
            {
                return ex.Message;
            }

        }

        public static  string HttpGet(string Url, string postDataStr)
        {
            try
            {
                //======================防止基础连接已经关闭: 未能为 SSL/TLS 安全通道建立信任关系
                //ServicePointManager.ServerCertificateValidationCallback += RemoteCertificateValidate;
                System.Net.ServicePointManager.ServerCertificateValidationCallback = new System.Net.Security.RemoteCertificateValidationCallback(RemoteCertificateValidate);
                //========================
                HttpWebRequest request = (HttpWebRequest)WebRequest.Create(Url + (postDataStr == "" ? "" : "?") + postDataStr);
                request.Method = "GET";
                request.ContentType = "application/json; charset=utf-8";
                //头里面要带入token
                request.Headers.Add("Cookie", "token=acMyRwXZg");                
                HttpWebResponse response = (HttpWebResponse)request.GetResponse();
                Stream myResponseStream = response.GetResponseStream();
                StreamReader myStreamReader = new StreamReader(myResponseStream, Encoding.GetEncoding("utf-8"));
                string retString = myStreamReader.ReadToEnd();
                myStreamReader.Close();
                myResponseStream.Close();
                return retString;
            }
            catch (Exception ex)
            { return ex.Message; }
                
        }


        
        private static bool RemoteCertificateValidate(object sender, X509Certificate cert, X509Chain chain, SslPolicyErrors error)
        {
            //为了通过证书验证，总是返回true
            return true;
        }

        public static bool SetLocalTimeByStr(string timestr)
        {
            bool flag=false;
            SystemTime sysTime =new SystemTime();
           DateTime dt= Convert.ToDateTime(timestr);
            string SysTime=timestr.Trim();   //此步骤多余，为方便程序而用直接用timestr即可
            sysTime.year = Convert.ToUInt16(dt.Year);
            sysTime.month = Convert.ToUInt16(dt.Month);
            sysTime.day = Convert.ToUInt16(dt.Day);
            sysTime.hour = Convert.ToUInt16(dt.Hour);
            sysTime.minute = Convert.ToUInt16(dt.Minute);
            sysTime.second = Convert.ToUInt16(dt.Second);
            //注意：
            //结构体的wDayOfWeek属性一般不用赋值，函数会自动计算，写了如果不对应反而会出错
            //wMiliseconds属性默认值为一，可以赋值
            try
            {
                flag=SetLocalTime(ref sysTime);
            }
            //由于不是C#本身的函数，很多异常无法捕获
           //函数执行成功则返回true，函数执行失败返回false
           //经常不返回异常，不提示错误，但是函数返回false，给查找错误带来了一定的困难
            catch(Exception ex1)
            {
               // Logger.Write("SetLocalTimeByStr:"+ex1.ToString());
                Console.WriteLine("SetLocalTime函数执行异常"+ex1.Message);
            }

            return flag;
        }
       
        [StructLayout(LayoutKind.Sequential)]
        struct SystemTime
        {
            [MarshalAs(UnmanagedType.U2)]
            internal ushort year; // 年
            [MarshalAs(UnmanagedType.U2)]
            internal ushort month; // 月
            [MarshalAs(UnmanagedType.U2)]
            internal ushort dayOfWeek; // 星期
            [MarshalAs(UnmanagedType.U2)]
            internal ushort day; // 日
            [MarshalAs(UnmanagedType.U2)]
            internal ushort hour; // 时
            [MarshalAs(UnmanagedType.U2)]
            internal ushort minute; // 分
            [MarshalAs(UnmanagedType.U2)]
            internal ushort second; // 秒
            [MarshalAs(UnmanagedType.U2)]
            internal ushort milliseconds; // 毫秒
        }

        
    }

    public class TimeData
    {
        public string sj { get; set; }
    }

    

    
}
