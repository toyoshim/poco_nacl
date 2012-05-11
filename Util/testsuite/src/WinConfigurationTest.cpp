//
// WinConfigurationTest.cpp
//
// $Id: //poco/1.4/Util/testsuite/src/WinConfigurationTest.cpp#1 $
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "WinConfigurationTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Util/WinRegistryConfiguration.h"
#include "Poco/Environment.h"
#include "Poco/AutoPtr.h"


using Poco::Util::WinRegistryConfiguration;
using Poco::Environment;
using Poco::AutoPtr;


WinConfigurationTest::WinConfigurationTest(const std::string& name): CppUnit::TestCase(name)
{
}


WinConfigurationTest::~WinConfigurationTest()
{
}


void WinConfigurationTest::testConfiguration()
{
	AutoPtr<WinRegistryConfiguration> pReg = new WinRegistryConfiguration("HKEY_CURRENT_USER\\Software\\Applied Informatics\\Test");
	pReg->setString("name1", "value1");
	assert (pReg->getString("name1") == "value1");
	pReg->setInt("name1", 1); // overwrite should also change type
	assert (pReg->getInt("name1") == 1);
	pReg->setString("name2", "value2");
	assert (pReg->getString("name2") == "value2");
	assert (pReg->hasProperty("name1"));
	assert (pReg->hasProperty("name2"));
	
	std::string dfl = pReg->getString("nonexistent", "default");
	assert (dfl == "default");
	
	AutoPtr<Poco::Util::AbstractConfiguration> pView = pReg->createView("config");
	dfl = pView->getString("sub.foo", "default");
	assert (dfl == "default");
	
	pView->setString("sub.foo", "bar");
	assert (pView->getString("sub.foo", "default") == "bar");
}


void WinConfigurationTest::setUp()
{
}


void WinConfigurationTest::tearDown()
{
}


CppUnit::Test* WinConfigurationTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("WinConfigurationTest");

	CppUnit_addTest(pSuite, WinConfigurationTest, testConfiguration);

	return pSuite;
}
