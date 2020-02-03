using System;
using System.Windows;
using Microsoft.Xna.Framework;

namespace ZurrapaDLL.Utils
{
    class Maths
    {
        public static double GetRandomFloat(double start, double end)
        {
            return new Random().NextDouble() * (end - start) + start;
        }

        public static double GetFOV(Vector2 vecAngles, Vector2 vecSrc, Vector2 vecDst)
        {
            var Ang = CalculateAngle(vecSrc, vecDst);
            var AngToVector = new Vector2(Ang);

            var mag = Math.Pow(Math.Sqrt(vecAngles.Length()), 2);
            var dot = Vector2.Dot(vecAngles, AngToVector);
            
            return Math.Acos(dot / mag) * (180.0 / Math.PI);
        }

        public static Vector2 ClampVector(Vector2 vecIn)
        {
            return Vector2.Clamp(vecIn, new Vector2(-89.0f, -180.0f), new Vector2(180.0f, 360.0f));
        }

        public static Vector2 PerfectRecoildControl(Vector2 vecPunchAngle)
        {
            var len = Vector2.Normalize(vecPunchAngle).Length();

            len -= (10.0f + len * 0.5f) * 0.015625f;
            len = Math.Max(len, 0.0f);

            vecPunchAngle.X *= len;
            vecPunchAngle.Y *= len;
            
            return vecPunchAngle;
        }

        private static float CalculateAngle(Vector2 vecSrc, Vector2 vecDst)
        {
            return MathHelper.ToDegrees((float)Math.Atan2(vecSrc.Y - vecDst.Y, vecSrc.X - vecDst.X));
        }
    }
}
