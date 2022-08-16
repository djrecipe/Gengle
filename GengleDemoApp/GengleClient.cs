namespace GengleDemoApp
{
    internal class GengleClient
    {
        public GengleClient()
        {
            NativeLibrary library = new NativeLibrary("GengleInterop.dll");
            GengleInterop.Initialize(library);
        }

        public void Demo()
        {
            GengleInterop.Demo();
        }
    }
}
