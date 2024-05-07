//////////////////////////////////////////////////////////////////////////////////////
//
//   J/Link source code (c) 1999-2022, Wolfram Research, Inc. All rights reserved.
//
//   Use is governed by the terms of the J/Link license agreement, which can be found at
//   www.wolfram.com/solutions/mathlink/jlink.
//
//   Author: Todd Gayley
//
//////////////////////////////////////////////////////////////////////////////////////

package com.wolfram.jlink;

import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import jdk.jshell.execution.LoaderDelegate;
import jdk.jshell.spi.ExecutionControl.ClassBytecodes;
import jdk.jshell.spi.ExecutionControl.EngineTerminationException;
import jdk.jshell.spi.ExecutionControl.InternalException;
import jdk.jshell.spi.ExecutionControl.ClassInstallException;

import java.io.File;

/**
 * This is a subclass of JLinkClassLoader that is used in Java 9 and later. It has functionality to support ExternalEvaluate in WL, specifically
 * by implementing the LoaderDelegate interface, so J/Link and the JShell used by ExternalEvaluate can share the same classes.
 */

public class JLinkClassLoader9 extends JLinkClassLoader implements LoaderDelegate {


    /**
     * Constructs a new JLinkClassLoader9 instance. Only advanced programmers will need to use this.
     *
     * @since 3.0
     */
    public JLinkClassLoader9() {
        super();
    }

    /**
     * Constructs a new JLinkClassLoader9 instance that has the given class loader as its parent loader.
     * Only advanced programmers will need to use this.
     *
     * @since 3.0
     */
    public JLinkClassLoader9(ClassLoader parent) {
		super(parent);
	}

	
	///////////////////////////////////  LoaderDelegate implementation  ////////////////////////////////////
    
 	
    // Inspired by code from the JDK: https://java-browser.yawk.at/java/11/jdk.jshell/jdk/jshell/execution/DefaultLoaderDelegate.java

    private final Map<String, Class<?>> klasses = new HashMap<>();

    private final Map<String, ClassFile> classFiles = new HashMap<>();


    @Override
    Class<?> findLoadedClassExposed(String name) {
        // Before loooking in helper, see if this is a previously-loaded jshell-generated class (that is, in klasses).
        Class<?> klass = klasses.get(name);
        if (klass != null) {
            return klass;
        }
        // Now look to see if this is an as-yet-not-loaded jshell-generated class.
        ClassFile file = classFiles.get(name);
        if (file != null) {
            return super.defineClass(name, file.data, 0, file.data.length);
        }
        // Didn't find it among jshell-generated classes; look among standard J/Link-loaded classes.
        return super.findLoadedClassExposed(name);
    }

    
	@Override
    public void load(ClassBytecodes[] cbcs) throws ClassInstallException, EngineTerminationException {
        boolean[] loaded = new boolean[cbcs.length];
        try {
            for (ClassBytecodes cbc : cbcs) {
                declare(cbc.name(), cbc.bytecodes());
            }
            for (int i = 0; i < cbcs.length; ++i) {
                ClassBytecodes cbc = cbcs[i];
                Class<?> klass = loadClass(cbc.name());
                klasses.put(cbc.name(), klass);
                loaded[i] = true;
                // Get class loaded to the point of, at least, preparation
                klass.getDeclaredMethods();
            }
        } catch (Throwable ex) {
            throw new ClassInstallException("load: " + ex.getMessage(), loaded);
        }
    }

    @Override
    public void classesRedefined(ClassBytecodes[] cbcs) {
        for (ClassBytecodes cbc : cbcs) {
            declare(cbc.name(), cbc.bytecodes());
        }
    }

    @Override
    public void addToClasspath(String cp) throws EngineTerminationException, InternalException {
        try {
            List<URL> urls = new ArrayList<URL>();
            for (String path : cp.split(File.pathSeparator)) {
                urls.add(new File(path).toURI().toURL());
            }
            addAll(urls, false);
        } catch (Exception ex) {
            throw new InternalException(ex.toString());
        }
    }

    @Override
    public Class<?> findClass(String name) throws ClassNotFoundException {
        return helper.findClass(name);
    }

    private void declare(String name, byte[] bytes) {
        classFiles.put(name, new ClassFile(bytes, System.currentTimeMillis()));
    }
	

    private static class ClassFile {
        public final byte[] data;
        public final long timestamp;

        ClassFile(byte[] data, long timestamp) {
            this.data = data;
            this.timestamp = timestamp;
        }
    }

}

