using System;
using System.IO;
using System.Collections.Generic;
using System.Runtime.Serialization;

namespace NativeFunctionTranslator
{
    class Program
    {
        public static List<string> GetFileListWithExtend(DirectoryInfo directory, string pattern)
        {
            List<string> pathList = new List<string>();
            string result = string.Empty;
            if (directory.Exists || pattern.Trim() != string.Empty)
            {
                foreach (FileInfo info in directory.GetFiles(pattern))
                {
                    result = info.FullName.ToString();
                    pathList.Add(result);
                }
            }
            return pathList;
        }

        static void Main(string[] args)
        {
            DirectoryInfo directory = new DirectoryInfo(Environment.CurrentDirectory);

            string MinConsoleFolder = directory.Parent.Parent.Parent.Parent.Parent.ToString();

            //try to read
            string targetFolder = Path.Combine(MinConsoleFolder, "src\\MinConsoleNative");
            //try to write
            string targetFile = Path.Combine(MinConsoleFolder, "src\\MinConsole\\MinConsoleNativeFuncs.cs");

            List<string> headFiles = GetFileListWithExtend(new DirectoryInfo(targetFolder), "*.h");

            const string EXPORT_FUNC = "EXPORT_FUNC";

            List<string> nativeMethodDeclaration = new List<string>();

            foreach (string headFile in headFiles)
            {
                string text = File.ReadAllText(headFile);
                string[] lines = text.Split(Environment.NewLine);

                foreach (string line in lines)
                {
                    string _line = line.Trim();

                    if (_line.IndexOf(EXPORT_FUNC) != -1)
                    {
                        bool equal = true;
                        for (int i = 0; i < EXPORT_FUNC.Length; i++)
                        {
                            if (_line[i] != EXPORT_FUNC[i])
                            {
                                equal = false;
                                break;
                            }
                        }

                        if (equal && !nativeMethodDeclaration.Contains(_line))
                        {
                            nativeMethodDeclaration.Add(_line);
                        }
                    }
                }

                continue;
            }

            Console.WriteLine("Hello World!");
            Console.ReadKey();
        }
    }
}
