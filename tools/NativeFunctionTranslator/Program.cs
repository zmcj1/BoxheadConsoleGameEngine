#define ENABLE_DEBUG

using System;
using System.IO;
using System.Collections.Generic;
using System.Text;

//Version:2.3

namespace NativeFunctionTranslator
{
    public enum ParamType
    {
        None = 0,
        In = 1,
        Out = 2,
        Ref = 3,
        Array = 4,
    }

    public struct Param
    {
        public string VarType;
        public string VarName;

        public Param(string VarType, string VarName)
        {
            this.VarType = VarType;
            this.VarName = VarName;
        }
    }

    public class ParamList
    {
        public List<Param> paramList = new List<Param>();

        public override string ToString()
        {
            string str = string.Empty;
            for (int i = 0; i < paramList.Count; i++)
            {
                Param param = paramList[i];
                //single param or last param
                if (paramList.Count == 1 || i == paramList.Count - 1)
                {
                    if (param.VarType == string.Empty && param.VarName == string.Empty)
                    {
                        break;
                    }
                    else
                    {
                        str += param.VarType + " " + param.VarName;
                    }
                }
                else
                {
                    str += param.VarType + " " + param.VarName + ", ";
                }
            }
            return str;
        }
    }

    public class Program
    {
        public const string EXPORT_FUNC = "EXPORT_FUNC";
        public const string EXPORT_FUNC_EX = "EXPORT_FUNC_EX";
        public const string EXPORT_FUNC_DLLIMPORT = "[DllImport(\"MinConsoleNative.dll\", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]";
        public const string EXPORT_FUNC_RETURN_TYPE = "public extern static bool";
        public const string EXPORT_FUNC_RETURN_TYPE_EX = "public extern static ";
        public const int EXPORT_FUNC_INDENT = 8;
        public static string IndentString = null;

        public const string _IN_ = "_IN_";
        public const string _OUT_ = "_OUT_";
        public const string _REF_ = "_REF_";
        public const string _ARRAY_ = "_ARRAY_";

        public const string DECLARATION =
@"////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                    MinConsole
//    On April 11, 2021, this project is officially open source!
//
//    Made in Minsk, Belarus.
//
//    IMPORTANT: This document will change at any time.
//
//    This project is in the early development stage, everything is changing at a high speed!
//
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    MIT License
//
//    Copyright (c) 2021 Min. All rights reserved.
//
//    Permission is hereby granted, free of charge, to any person obtaining a copy
//    of this software and associated documentation files (the 'Software'), to deal
//    in the Software without restriction, including without limitation the rights
//    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//    copies of the Software, and to permit persons to whom the Software is
//    furnished to do so, subject to the following conditions:
//
//    The above copyright notice and this permission notice shall be included in all
//    copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//    SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Contact greatdestroyercharlie@gmail.com with questions or concerns
//
////////////////////////////////////////////////////////////////////////////////////////////////////";

        public static bool DebugPause = false;

        public static List<string> GetFileListWithExtend(DirectoryInfo directory, string pattern)
        {
            List<string> pathList = new List<string>();
            if (directory.Exists || pattern.Trim() != string.Empty)
            {
                foreach (FileInfo info in directory.GetFiles(pattern))
                {
                    pathList.Add(info.FullName.ToString());
                }
            }
            return pathList;
        }

        public static string GetIndentString()
        {
            if (IndentString == null)
            {
                StringBuilder builder = new StringBuilder();
                for (int i = 0; i < EXPORT_FUNC_INDENT; i++)
                {
                    builder.Append(' ');
                }
                IndentString = builder.ToString();
                return IndentString;
            }
            else
            {
                return IndentString;
            }
        }

        public static List<string> GetHeadLines()
        {
            List<string> lines = new List<string>();
            lines.Add("using System;");
            lines.Add("using System.Runtime.InteropServices;");
            lines.Add("using static MinConsole.MinConsoleNativeStructs;");
            lines.Add("");
            lines.Add("namespace MinConsole");
            lines.Add("{");
            lines.Add("    //This class is auto generated by NativeFunctionTranslator.");
            lines.Add("    internal static class MinConsoleNativeFuncs");
            lines.Add("    {");
            return lines;
        }

        public static List<string> GetTailLines()
        {
            List<string> lines = new List<string>();
            lines.Add("    }");
            lines.Add("}");
            return lines;
        }

        public static List<string> GetNativeMethodsDeclaration(List<string> headFiles)
        {
            List<string> nativeMethodDeclaration = new List<string>();

            foreach (string headFile in headFiles)
            {
                string text = File.ReadAllText(headFile);
                string[] lines = text.Split(Environment.NewLine);

                foreach (string line in lines)
                {
                    string lineWithOutSpace = line.Trim();

                    if (lineWithOutSpace.IndexOf(EXPORT_FUNC) == -1) continue;

                    //Make sure this is a method declaration
                    bool equal = true;
                    for (int i = 0; i < EXPORT_FUNC.Length; i++)
                    {
                        if (lineWithOutSpace[i] != EXPORT_FUNC[i])
                        {
                            equal = false;
                            break;
                        }
                    }
                    //Don't add duplicate methods
                    if (equal && !nativeMethodDeclaration.Contains(lineWithOutSpace))
                    {
                        nativeMethodDeclaration.Add(lineWithOutSpace);
                    }
                }
            }

            return nativeMethodDeclaration;
        }

        public static List<string> ParseNativeMethodDeclaration(List<string> nativeMethodsDeclaration)
        {
            List<string> nativeMethodNewDeclaration = new List<string>();

            foreach (string item in nativeMethodsDeclaration)
            {
                string declaration = null;
                string methodName = null;

                //try to find EXPORT_FUNC_EX
                if (item.IndexOf(EXPORT_FUNC_EX) != -1)
                {
                    int _leftBracketIndex = item.IndexOf('(');
                    int _rightBracketIndex = item.IndexOf(')');
                    string returnType = item.Substring(_leftBracketIndex + 1, _rightBracketIndex - _leftBracketIndex - 1);

                    declaration += EXPORT_FUNC_RETURN_TYPE_EX;
                    declaration += returnType;
                    declaration += item.Substring(_rightBracketIndex + 1, item.Length - _rightBracketIndex - 1);

                    methodName = declaration.Substring((EXPORT_FUNC_RETURN_TYPE_EX + returnType + 1).Length,
                        declaration.IndexOf('(') - (EXPORT_FUNC_RETURN_TYPE_EX + returnType).Length - 1);
                }
                else
                {
                    declaration = item.Replace(EXPORT_FUNC, EXPORT_FUNC_RETURN_TYPE);

                    methodName = item.Split(' ')[1].Substring(0, item.IndexOf('(') - EXPORT_FUNC.Length - 1);
                }

                int leftBracketIndex = declaration.IndexOf('(');
                int rightBracketIndex = declaration.IndexOf(')');

                string parameters = declaration.Substring(leftBracketIndex + 1, rightBracketIndex - leftBracketIndex - 1);
#if ENABLE_DEBUG
                if (methodName.IndexOf("Min") != 0)
                {
                    DebugPause = true;
                    Console.ForegroundColor = ConsoleColor.White;
                    Console.Write(methodName);
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.BackgroundColor = ConsoleColor.White;
                    Console.WriteLine(" does not contain Min!");
                    Console.ForegroundColor = ConsoleColor.Gray;
                    Console.BackgroundColor = ConsoleColor.Black;
                }
#endif
                ParamList newParameters = new ParamList();

                //void parameters
                if (string.IsNullOrEmpty(parameters))
                {
                    newParameters.paramList.Add(new Param("", ""));
                }
                else
                {
                    string[] paramDefines = parameters.Split(',');
                    foreach (string paramDefine in paramDefines)
                    {
                        string varType = string.Empty;
                        //param modifier
                        ParamType paramType = ParamType.None;

                        //get symbols
                        string[] symbols = paramDefine.Split(' ');
                        //varName is the last paramDefine
                        string varName = symbols[symbols.Length - 1];

                        //Analyze every symbol of each parameter
                        for (int i = 0; i < symbols.Length - 1; i++)
                        {
                            string symbol = symbols[i];
                            //Check Parameter transfer modifier first:
                            //in
                            if (symbol == _IN_)
                            {
                                paramType = ParamType.In;
                            }
                            //out
                            else if (symbol == _OUT_)
                            {
                                paramType = ParamType.Out;
                            }
                            //ref
                            else if (symbol == _REF_)
                            {
                                paramType = ParamType.Ref;
                            }
                            //array
                            else if (symbol == _ARRAY_)
                            {
                                paramType = ParamType.Array;
                            }
                        }
#if ENABLE_DEBUG
                        if (paramType == ParamType.None)
                        {
                            DebugPause = true;
                            Console.ForegroundColor = ConsoleColor.White;
                            Console.Write(methodName);
                            Console.ForegroundColor = ConsoleColor.Yellow;
                            Console.Write('.');
                            Console.Write(varName);
                            Console.ForegroundColor = ConsoleColor.Red;
                            Console.WriteLine(" does not contain any ParamType");
                            Console.ForegroundColor = ConsoleColor.Gray;
                        }
#endif
                        //Analyze every symbol of each parameter
                        for (int i = 0; i < symbols.Length - 1; i++)
                        {
                            string symbol = symbols[i];
                            //ignore C++ const symbol
                            if (symbol == "const")
                            {
                                continue;
                            }
                            //Check type
                            bool isPointerType = false;
                            int ptrIndex = symbol.LastIndexOf('*');
                            //use this
                            string _symbol = symbol;
                            //is pointer
                            if (ptrIndex != -1)
                            {
                                _symbol = symbol.Substring(0, ptrIndex);
                                isPointerType = true;
                            }
                            //Only pointers need to judge ParamType
                            if (isPointerType)
                            {
                                switch (paramType)
                                {
                                    case ParamType.None:
                                    case ParamType.In:
                                        if (_symbol == "wchar*")
                                        {
                                            varType = "ref string";
                                        }
                                        else if (_symbol == "DWORD")
                                        {
                                            varType = "ref uint";
                                        }
                                        else if (_symbol == "wchar")
                                        {
                                            varType = "string";
                                        }
                                        else if (_symbol == "HWND")
                                        {
                                            varType = "IntPtr";
                                        }
                                        else if (_symbol == "FARPROC")
                                        {
                                            varType = "ref object";
                                        }
                                        else if (_symbol == "HANDLE")
                                        {
                                            varType = "ref IntPtr";
                                        }
                                        else
                                        {
                                            varType = "ref " + _symbol;
                                        }
                                        break;
                                    case ParamType.Out:
                                        if (_symbol == "wchar*")
                                        {
                                            varType = "out string";
                                        }
                                        else if (_symbol == "wchar")
                                        {
                                            varType = "out string";
                                        }
                                        else if (_symbol == "HWND")
                                        {
                                            varType = "out IntPtr";
                                        }
                                        else if (_symbol == "FARPROC")
                                        {
                                            varType = "out object";
                                        }
                                        else if (_symbol == "HANDLE")
                                        {
                                            varType = "out IntPtr";
                                        }
                                        else
                                        {
                                            varType = "out " + _symbol;
                                        }
                                        break;
                                    case ParamType.Array:
                                        if (_symbol == "wchar*")
                                        {
                                            varType = "string[]";
                                        }
                                        else if (_symbol == "wchar")
                                        {
                                            varType = "char[]";
                                        }
                                        else if (_symbol == "HWND")
                                        {
                                            varType = "IntPtr[]";
                                        }
                                        else if (_symbol == "FARPROC")
                                        {
                                            varType = "object[]";
                                        }
                                        else if (_symbol == "HANDLE")
                                        {
                                            varType = "IntPtr[]";
                                        }
                                        else
                                        {
                                            varType = _symbol + "[]";
                                        }
                                        break;
                                    case ParamType.Ref:
                                        if (_symbol == "wchar*")
                                        {
                                            varType = "ref string";
                                        }
                                        else if (_symbol == "wchar")
                                        {
                                            varType = "ref char";
                                        }
                                        else if (_symbol == "HWND")
                                        {
                                            varType = "ref IntPtr";
                                        }
                                        else if (_symbol == "FARPROC")
                                        {
                                            varType = "ref object";
                                        }
                                        else if (_symbol == "HANDLE")
                                        {
                                            varType = "ref IntPtr";
                                        }
                                        else
                                        {
                                            varType = "ref " + _symbol;
                                        }
                                        break;
                                }
                            }
                            else
                            {
                                if (_symbol == "HWND")
                                {
                                    varType = "IntPtr";
                                }
                                else if (_symbol == "DWORD")
                                {
                                    varType = "uint";
                                }
                                else if (_symbol == "HICON")
                                {
                                    varType = "ref ICON";
                                }
                                else if (_symbol == "wchar")
                                {
                                    varType = "char";
                                }
                                else if (_symbol == "HANDLE")
                                {
                                    varType = "IntPtr";
                                }
                                else
                                {
                                    varType = _symbol;
                                }
                            }
                        }

                        //add
                        newParameters.paramList.Add(new Param(varType, varName));
                    }
                }

                //add DllImport
                nativeMethodNewDeclaration.Add(GetIndentString() + EXPORT_FUNC_DLLIMPORT);
                //new Declaration
                string newDeclaration = declaration.Substring(0, leftBracketIndex + 1) + newParameters.ToString() + ");";
                nativeMethodNewDeclaration.Add(GetIndentString() + newDeclaration);
                //newline
                nativeMethodNewDeclaration.Add("");
            }

            return nativeMethodNewDeclaration;
        }

        public static void GenMinConsoleNativeFuncs(string MinConsoleFolder, List<string> headFiles)
        {
            string MinConsoleNativeFuncsFile = Path.Combine(MinConsoleFolder, "src\\MinConsole\\MinConsoleNativeFuncs.cs");

            List<string> nativeMethodsDeclaration = GetNativeMethodsDeclaration(headFiles);

            //native method result
            List<string> nativeMethodNewDeclaration = ParseNativeMethodDeclaration(nativeMethodsDeclaration);

            //final handling
            List<string> finalLines = new List<string>();
            //add head
            finalLines.AddRange(GetHeadLines());
            //add content
            finalLines.AddRange(nativeMethodNewDeclaration);
            //add tail
            finalLines.AddRange(GetTailLines());

            //add NewLine
            StringBuilder stringBuilder = new StringBuilder();
            finalLines.ForEach(item => { stringBuilder.Append(item + Environment.NewLine); });
            //write to file
            File.WriteAllText(MinConsoleNativeFuncsFile, stringBuilder.ToString(), Encoding.UTF8);
        }

        public static void GenMinConsoleNative(string MinConsoleNativeFolder, List<string> headFiles)
        {
            List<FileInfo> headFileInfos = new List<FileInfo>();
            headFiles.ForEach(str => { headFileInfos.Add(new FileInfo(str)); });

            StringBuilder stringBuilder2 = new StringBuilder();
            stringBuilder2.Append("//This file is auto-generated.\n");
            stringBuilder2.Append("#pragma once\n\n");
            headFileInfos.ForEach(fileInfo => { stringBuilder2.Append("#include \"" + fileInfo.Name + "\"\n"); });
            stringBuilder2.Append("using namespace MinConsoleNative;\n");

            string MinConsoleNativeHeadFilePath = Path.Combine(MinConsoleNativeFolder, "MinConsoleNative.h");
            File.WriteAllText(MinConsoleNativeHeadFilePath, stringBuilder2.ToString(), Encoding.UTF8);
        }

        public static void GenMinConsoleHeaderFileDeclarationAndLicense(List<string> headFiles, List<string> sourceFiles, bool add)
        {
            //const var
            byte[] UTF8BOM = new byte[3];
            UTF8BOM[0] = 0xEF;
            UTF8BOM[1] = 0xBB;
            UTF8BOM[2] = 0xBF;

            List<string> filesNeedToRead = new List<string>();
            filesNeedToRead.AddRange(headFiles);
            filesNeedToRead.AddRange(sourceFiles);
            //filesNeedToRead.Add(headFiles[0]); //for testing

            foreach (string filePath in filesNeedToRead)
            {
                bool isUTF8BOMFile = true;

                //check if they are all encoding in UTF-8.
                using (FileStream stream = new FileStream(filePath, FileMode.Open))
                {
                    for (int i = 0; i < 3; i++)
                    {
                        int readByte = stream.ReadByte();
                        if (readByte != UTF8BOM[i])
                        {
                            isUTF8BOMFile = false;
                            break;
                        }
                    }
                    if (!isUTF8BOMFile)
                    {
                        //warning!!!!!
                        Console.BackgroundColor = ConsoleColor.Magenta;
                        Console.WriteLine($"{filePath} is not UTF-8 Encoding, Now I rewrite it in UTF-8.");
                        Console.BackgroundColor = ConsoleColor.Black;
                    }
                }

                //add declaration or remove it.
                if (add)
                {
                    string code = File.ReadAllText(filePath, Encoding.UTF8);
                    string newCode = DECLARATION + "\n" + code;
                    File.WriteAllText(filePath, newCode, Encoding.UTF8);
                }
                else
                {
                    string code = File.ReadAllText(filePath, Encoding.UTF8);
                    string newCode = code.Replace(DECLARATION + "\n", string.Empty);
                    File.WriteAllText(filePath, newCode, Encoding.UTF8);
                }
            }
        }

        public static void Main()
        {
            //Common
            DirectoryInfo currentDirectory = new DirectoryInfo(Environment.CurrentDirectory);
            string MinConsoleFolder = currentDirectory.Parent.Parent.Parent.Parent.Parent.ToString();
            string MinConsoleNativeFolder = Path.Combine(MinConsoleFolder, "src\\MinConsoleNative");
            List<string> headFiles = GetFileListWithExtend(new DirectoryInfo(MinConsoleNativeFolder), "*.h");
            List<string> sourceFiles = GetFileListWithExtend(new DirectoryInfo(MinConsoleNativeFolder), "*.cpp");

            //-----------generate MinConsoleNativeFuncs.cs-----------
            GenMinConsoleNativeFuncs(MinConsoleFolder, headFiles);

            //-----------generate MinConsoleNative.h-----------
            GenMinConsoleNative(MinConsoleNativeFolder, headFiles);

            //-----------generate MinConsoleHeaderFileDeclaration and License-----------
            //GenMinConsoleHeaderFileDeclarationAndLicense(headFiles, sourceFiles, true);

            //-----------for debugging-----------
#if ENABLE_DEBUG
            if (DebugPause)
            {
                Console.ReadLine();
            }
#endif
        }
    }
}