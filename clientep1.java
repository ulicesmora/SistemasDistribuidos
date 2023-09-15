import java.io.*;
import java.net.*;

public class clientep1 {
    public static void main(String[] args) {

	if (args.length != 2) {
            System.err.println(
                "Uso desde consola: java Cliente <nombre de host (computadora)> <numero puerto>");
            System.exit(1);
        }

	String nombreHost = args[0];
        int numeroPuerto = Integer.parseInt(args[1]);

        try {
            Socket socket = new Socket(nombreHost, numeroPuerto);

            BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter output = new PrintWriter(socket.getOutputStream(), true);

            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

            int num;
	    String numStr;
            do {
                System.out.print("Ingrese un número entero (0 para salir): ");
                //num = Integer.parseInt(reader.readLine());
		numStr = reader.readLine();

                // Enviar el número al servidor
                //output.println(num);
		output.println(numStr);


                // Recibir la respuesta del servidor
                //int respuesta = Integer.parseInt(input.readLine().trim());
                //System.out.println("Respuesta del servidor: " + respuesta);
		
		String respuesta = input.readLine().trim();
                System.out.println("Respuesta del servidor: " + respuesta);

            } while (!numStr.equals("0")); //while (num != 0);

            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
