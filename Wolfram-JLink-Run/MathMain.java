// wolfram java

import com.wolfram.jlink.*;

public class MathMain {

        public static void main(String[] argv) {

                KernelLink ml = null;

                try {
                        String[] argv3 =  {"-linkmode", "launch", "-linkname", "C:/Program Files/Wolfram Research/Wolfram Engine/13.0/wolfram.exe"};
                        ml = MathLinkFactory.createKernelLink(argv3);
                } catch (MathLinkException e) {
                        System.out.println("Fatal error opening link: " + e.getMessage());
                        return;
                }

                try {
                        // Get rid of the initial InputNamePacket the kernel will send
                        // when it is launched.
                        ml.discardAnswer();
                        String result = ml.evaluateToOutputForm(argv[0], 0);
                        System.out.println(result);

                } catch (MathLinkException e) {
                        System.out.println("MathLinkException occurred: " + e.getMessage());
                } finally {
                        ml.close();
                }
        }
}