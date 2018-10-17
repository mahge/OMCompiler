/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-CurrentYear, Linköping University,
 * Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF GPL VERSION 3
 * AND THIS OSMC PUBLIC LICENSE (OSMC-PL).
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES RECIPIENT'S
 * ACCEPTANCE OF THE OSMC PUBLIC LICENSE.
 *
 * The OpenModelica software and the Open Source Modelica
 * Consortium (OSMC) Public License (OSMC-PL) are obtained
 * from Linköping University, either from the above address,
 * from the URLs: http://www.ida.liu.se/projects/OpenModelica or
 * http://www.openmodelica.org, and in the OpenModelica distribution.
 * GNU version 3 is obtained from: http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of  MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS
 * OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 */


/*
 Mahder.Gebremedhin@liu.se  2014-02-10
*/


#include <iostream>

#include "om_pm_interface.hpp"
#include "om_pm_model.hpp"


extern "C" {

using namespace openmodelica::parmodelica;
typedef Equation::FunctionType FunctionType;



void* PM_Model_create(const char* model_name, DATA* data, threadData_t* threadData) {
    OMModel* pm_om_model = new OMModel(model_name);
    pm_om_model->data = data;
    pm_om_model->threadData = threadData;
    return pm_om_model;
}

void PM_Model_load_ODE_system(void* v_model, FunctionType* ode_system_funcs) {

    OMModel& model = *(static_cast<OMModel*>(v_model));
    model.ode_system_funcs = ode_system_funcs;
    model.load_ODE_system();
}


// void PM_functionInitialEquations(int size, FunctionType* functionInitialEquations_systems) {

    // // pm_om_model.ini_system_funcs = functionInitialEquations_systems;
    // // pm_om_model.INI_scheduler.execute();
    // pm_om_model.INI_scheduler.execution_timer.start_timer();
    // for(int i = 0; i < size; ++i)
        // functionInitialEquations_systems[i](data, threadData);
    // pm_om_model.INI_scheduler.execution_timer.stop_timer();

// }


// void PM_functionDAE(int size, FunctionType* functionDAE_systems) {

    // // pm_om_model.dae_system_funcs = functionDAE_systems;
    // // pm_om_model.DAE_scheduler.execute();

    // pm_om_model.DAE_scheduler.execution_timer.start_timer();
    // for(int i = 0; i < size; ++i)
        // functionDAE_systems[i](data, threadData);
    // pm_om_model.DAE_scheduler.execution_timer.stop_timer();

// }


void PM_evaluate_ODE_system(void* v_model) {

    OMModel& model = *(static_cast<OMModel*>(v_model));
    model.ODE_scheduler.execute();

    // pm_om_model.ODE_scheduler.execution_timer.start_timer();
    // for(int i = 0; i < size; ++i)
        // functionODE_systems[i](data, threadData);
    // pm_om_model.ODE_scheduler.execution_timer.stop_timer();

}

// void PM_functionAlg(int size, DATA* data, threadData_t* threadData, FunctionType* functionAlg_systems) {

    // pm_om_model.ALG_scheduler.execution_timer.start_timer();

    // for(int i = 0; i < size; ++i)
        // functionAlg_systems[i](data, threadData);

    // pm_om_model.ALG_scheduler.execution_timer.start_timer();

// }

void dump_times(void* v_model) {
    OMModel& model = *(static_cast<OMModel*>(v_model));

    utility::log("") << "Total INI: " << model.INI_scheduler.execution_timer.get_elapsed_time() << std::endl;
    utility::log("") << "Total DAE: " << model.DAE_scheduler.execution_timer.get_elapsed_time() << std::endl;
    utility::log("") << "Total ODE: " << model.ODE_scheduler.execution_timer.get_elapsed_time() << std::endl;
    utility::log("") << "Total ALG: " << model.ALG_scheduler.execution_timer.get_elapsed_time() << std::endl;
    utility::log("") << "Total ODE loading: " << model.load_system_timer.get_elapsed_time() << std::endl;
    utility::log("") << "Total ODE Clustering: " << model.ODE_scheduler.clustering_timer.get_elapsed_time() << std::endl;
}




} // extern "C"