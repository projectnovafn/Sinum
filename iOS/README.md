# Sinum iOS

Sinum iOS is a versatile traffic redirection tool designed to streamline URL modification within your application. It achieves this by harnessing a custom **NSURLProtocol**, enabling the seamless redirection of traffic from one URL, such as https://example.com, to a specified destination—in this case, https://api.novafn.dev.

## Building & Usage

### **MacOS**

1. **Open Terminal:**
   - Launch the Terminal application on your MacOS system.

2. **Clone Sinum:**
   - Employ `git` to clone Sinum into your present directory.

     ```bash
     git clone https://github.com/projectnovafn/Sinum.git
     ```

3. **Navigate to the Sinum iOS Directory:**
   - Change into the Sinum iOS directory using the following command:

     ```bash
     cd Sinum/iOS
     ```

4. **Run the Build Script:**
   - Execute the build script by running the following command:

     ```bash
     ./build-mac.sh
     ```

### **Linux / Windows via WSL**

1. **Open Terminal:**
   - Launch the Linux terminal on Native Linux or via WSL.

2. **Install and Set Up cctools-port:**
   - To use cctools-port, follow the installation and setup instructions provided in the [cctools-port GitHub repository](https://github.com/tpoechtrager/cctools-port). Note that this tutorial does not include the distribution of proprietary Apple files.

3. **Clone Sinum:**
   - Employ `git` to clone Sinum into your present directory.

     ```bash
     git clone https://github.com/projectnovafn/Sinum.git
     ```

4. **Navigate to the Sinum iOS Directory:**
   - Change into the Sinum iOS directory using the following command:

     ```bash
     cd Sinum/iOS
     ```

5. **Run the Build Script:**
   - Execute the build script:

     ```bash
     ./build-linux.sh
     ```
