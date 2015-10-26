
import ucar.nc2.NetcdfFile;

import java.io.BufferedWriter;
import java.io.File;
//import java.io.FileFilter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.*;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
//import java.util.Collections;
import java.util.List;
import java.lang.String;


public class extractdatabin {
    private static String DELIMITER = "\t";

    public static void main(String[] args) throws IOException {

        if (args.length != 2) {
            System.exit(2);
        }

        System.out.println("Extracting Data");

        NetcdfFile nf = null;
        //NetcdfFile nfFileList = null;

        File rawdataDir = new File(args[0]);
        //File outdir = new File(args[1]);

        if (rawdataDir.exists()) {

            BufferedWriter brFileList = new BufferedWriter(new FileWriter(rawdataDir + "/FileList.txt"));
            StringBuilder sbFileList = new StringBuilder();

            List<String> files = list(rawdataDir);
            System.out.println("Printing the file list : ");
            for (String file : files) {
                System.out.println(file);
            }

            for (String file : files) {

                System.out.println(file);

                nf = NetcdfFile.open(file);

                String[] stationId = null;
                char[][] stations = (char[][]) nf.findVariable("stationId").read().copyToNDJavaArray();
                stationId = new String[stations.length];
                for (int n = 0; n < stations.length; n++)
                    stationId[n] = String.valueOf(stations[n]).trim();


                float[] lat = (float[]) nf.findVariable("latitude").read().copyTo1DJavaArray();
                float[] lon = (float[]) nf.findVariable("longitude").read().copyTo1DJavaArray();
                float[] windspd = (float[]) nf.findVariable("windSpeed").read().copyTo1DJavaArray();
                float[] winddir = (float[]) nf.findVariable("windDir").read().copyTo1DJavaArray();
                int[] wmo = (int[]) nf.findVariable("numericWMOid").read().copyTo1DJavaArray();
	    		

                Path filepath = Paths.get(file);
                String filename = filepath.getFileName().toString();
                String filepath1 = filepath.getParent().toString();

                //String filepathname = filepath.substring(0,absolutePath.lastIndexOf(filepath.));

                String newFileName = filepath1 + "/mesonet-" + filename + ".dat";

                System.out.println("newFileName : " + newFileName);

//                BufferedWriter br = new BufferedWriter(new FileWriter(newFileName));
//                StringBuilder sb = new StringBuilder();
                DataOutputStream dos = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(newFileName)));

                for(int i=0; i<windspd.length; i++)
                {
                    if( ( windspd[i] >= 0 && windspd[i] <=130) && (winddir[i]>=0 && winddir[i]<=360)
                            && ( lat[i]>=-90 && lat[i] <= 90 ) && ( lon[i]>=-180 && lon[i] <= 180 ) ) {

                        // writeUTF - First, two bytes are written to the output stream as if by the writeShort method giving the number of bytes to follow.
                        //check for missing Station ID
                        String stn = null;
                        if (stationId[i] == null) {
                            if (wmo[i] != -9999 && wmo[i] != -2147483647)
                                stn = String.valueOf(wmo[i]);
                            else
                                stn = String.valueOf(lat[i] + "-" + lon[i]);
                        }
                        else
                        {
                            stn = stationId[i];
                        }
                        // Force len 5
                        stn = stn.concat("     ").substring(0,5);
                        if(stn.length() < 5){
                            System.out.println(stn);
                        }

                        int spd = Math.round(windspd[i]*100);
                        int dir = Math.round(winddir[i]*100);
                        int intlat = Math.round(lat[i]*100);
                        int intlon = Math.round(lon[i]*100);

                        dos.writeBytes(stn);
                        if (stn.equals("AP061")) {
                            System.out.format("%d %d\n", spd, dir);
                        }

                        dos.writeInt(spd);
                        dos.writeInt(dir);
                        dos.writeInt(intlat);
                        dos.writeInt(intlon);

                    }
                }

                sbFileList.append(newFileName + "\n");

                dos.close();

            }

            brFileList.write(sbFileList.toString());
            brFileList.close();
        }


        //String file = "C:/Users/Pankaj/Desktop/mesonet/parser/src/gash/obs/tempdata/20130101_0000";

    }


    protected static List<String> list(File parent) {
        return listFiles(parent, parent);
    }

    protected static List<String> listFiles(File parent, File folder) {
        List<String> lstFiles = new ArrayList<String>(25);
        if (folder.isDirectory()) {

            File[] files = folder.listFiles();
            if (files != null) {
                for (File file : files) {
                    if (file.isDirectory()) {
                        lstFiles.addAll(listFiles(parent, file));
                    } else {
                        if(!file.getName().startsWith(".") && !file.getName().endsWith(".gz")  && !file.getName().endsWith(".txt")  && !file.getName().endsWith(".csv"))
                        {
                            //String path = file.getPath();
                            String path = file.getAbsolutePath();
                            //String offset = parent.getPath();

                            //path = path.substring(offset.length());
                            lstFiles.add(path);
                        }
                    }
                }
            }
        }

        return lstFiles;
    }

}

