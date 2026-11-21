// KKAnalyze.java - Ghidra headless post-script for the unpacked pno0001.exe
//   args: <labels.txt> <outdir>
// * creates functions + names from labels.txt ("hexaddr name" per line)
// * labels the KHandlers op table and the PTRTABLE
// * decompiles every function into <outdir>/decompiled_all.c and writes
//   <outdir>/functions.tsv (entry, name, size, callers)
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.nio.file.*;

public class KKAnalyze extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File outDir = new File(args[1]);
        outDir.mkdirs();
        SymbolTable st = currentProgram.getSymbolTable();
        int made = 0;
        for (String line : Files.readAllLines(Paths.get(args[0]))) {
            String[] p = line.trim().split("\\s+");
            if (p.length < 2) continue;
            Address a = toAddr(Long.parseLong(p[0], 16));
            disassemble(a);
            Function f = getFunctionAt(a);
            if (f == null) { f = createFunction(a, p[1]); made++; }
            if (f != null) f.setName(p[1], SourceType.USER_DEFINED);
            else st.createLabel(a, p[1], SourceType.USER_DEFINED);
        }
        st.createLabel(toAddr(0x83f328L), "KHandlers", SourceType.USER_DEFINED);
        st.createLabel(toAddr(0x83f800L), "PtrTable", SourceType.USER_DEFINED);
        st.createLabel(toAddr(0x82168cL), "DebugData_kx", SourceType.USER_DEFINED);
        println("created " + made + " functions from labels");

        // second analysis pass so new functions get their callees
        analyzeChanges(currentProgram);

        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        PrintWriter c = new PrintWriter(new FileWriter(new File(outDir, "decompiled_all.c")));
        PrintWriter t = new PrintWriter(new FileWriter(new File(outDir, "functions.tsv")));
        t.println("entry\tname\tsize\tcallers");
        c.println("/* pno0001.exe (.kkrieger, 2004) - Ghidra decompilation of the unpacked image */\n");
        int n = 0, failed = 0;
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            if (monitor.isCancelled()) break;
            n++;
            StringBuilder callers = new StringBuilder();
            for (Function cf : f.getCallingFunctions(monitor)) {
                if (callers.length() > 0) callers.append(',');
                callers.append(cf.getName());
            }
            t.println(f.getEntryPoint() + "\t" + f.getName() + "\t" + f.getBody().getNumAddresses() + "\t" + callers);
            DecompileResults r = di.decompileFunction(f, 120, monitor);
            c.println("/* ---- " + f.getName() + " @ " + f.getEntryPoint() + " ---- */");
            if (r.decompileCompleted()) c.println(r.getDecompiledFunction().getC());
            else { c.println("/* decompile failed */\n"); failed++; }
        }
        c.close(); t.close();
        println("decompiled " + n + " functions, " + failed + " failed");
    }
}
