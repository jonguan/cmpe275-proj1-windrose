
import ucar.nc2.NetcdfFile;

import java.io.BufferedWriter;
import java.io.File;
//import java.io.FileFilter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
//import java.util.Collections;
import java.util.List;
import java.lang.String;


public class extractdata {
	private static String DELIMITER = "^";

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
	    		
	    		
	    		String[] stationName = null;
				char[][] tmp = (char[][]) nf.findVariable("stationName").read().copyToNDJavaArray();
				stationName = new String[tmp.length];
				for (int n = 0; n < tmp.length; n++)
				stationName[n] = String.valueOf(tmp[n]).trim();

				String[] stationId = null;
				tmp = (char[][]) nf.findVariable("stationId").read().copyToNDJavaArray();
				stationId = new String[tmp.length];
				for (int n = 0; n < tmp.length; n++)
				stationId[n] = String.valueOf(tmp[n]).trim();
				
				
				float[] lat = (float[]) nf.findVariable("latitude").read().copyTo1DJavaArray();
				float[] lon = (float[]) nf.findVariable("longitude").read().copyTo1DJavaArray();  		
	    		float[] windspd = (float[]) nf.findVariable("windSpeed").read().copyTo1DJavaArray();
	    		float[] winddir = (float[]) nf.findVariable("windDir").read().copyTo1DJavaArray();
	    		int[] wmo = (int[]) nf.findVariable("numericWMOid").read().copyTo1DJavaArray();
	    		
	    		/*
	    		System.out.println("stationName : =================================");
	    		System.out.println(stationName.length);
	    		System.out.println("stationId : =================================");
	    		System.out.println(stationId.length);
	    		System.out.println("latitude : =================================");
	    		System.out.println(lat.length);
	    		System.out.println("longitude : =================================");
	    		System.out.println(lon.length);	    		
	    		System.out.println("windspd : =================================");
	    		System.out.println(windspd.length);
	    		System.out.println("winddir : =================================");
	    		System.out.println(winddir.length);
	    		*/
	    		
	    		
	    		Path filepath = Paths.get(file);
	    		String filename = filepath.getFileName().toString();
	    		String filepath1 = filepath.getParent().toString();
	    		
	    		//String filepathname = filepath.substring(0,absolutePath.lastIndexOf(filepath.));
	    		
	    		String newFileName = filepath1 + "/mesonet-" + filename + ".csv";
	    		
	    		System.out.println("newFileName : " + newFileName);
	    		
	    		BufferedWriter br = new BufferedWriter(new FileWriter(newFileName));
	    		StringBuilder sb = new StringBuilder();
	    		for(int i=0; i<windspd.length; i++)
	    		{
	    			if( ( windspd[i] >= 0 && windspd[i] <=130) && (winddir[i]>=0 && winddir[i]<=360)
	    				  && ( lat[i]>=-90 && lat[i] <= 90 ) && ( lon[i]>=-180 && lon[i] <= 180 )
	    				  && stationName[i] != null) {
	    				sb.append(stationName[i]);
	    				sb.append(DELIMITER);
	    				//check for missing Station ID
	    				if (stationId[i] == null) {
	    					if (wmo[i] != -9999 && wmo[i] != -2147483647)
	    						sb.append(String.valueOf(wmo[i]));
	    					else
	    						sb.append(String.valueOf(lat[i] + "-" + lon[i]));
	    				}
	    				else
	    				{
	    					sb.append(stationId[i]);
	    				}
	    				sb.append(DELIMITER);
	    				sb.append(String.format("%.2f", windspd[i]));
	    				sb.append(DELIMITER);
	    				sb.append(String.format("%.2f", winddir[i]));
	    				sb.append(DELIMITER);
	    				sb.append(String.format("%.2f", lat[i]));
	    				sb.append(DELIMITER);
	    				sb.append(String.format("%.2f", lon[i]));
	    				sb.append("\n");
	    			}
	    		}
	    		
	            sbFileList.append(newFileName + "\n");

	    		br.write(sb.toString());
	    		br.close();	
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

