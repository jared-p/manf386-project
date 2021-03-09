%%-----------------------------------------------------------------------------------------------------------------
% SIEMENS AG
% RC-DE PD CSO 1 SD3 2
% � Copyright 2018. All Rights Reserved.
%------------------------------------------------------------------------------------------------------------------
% Functionality provided by this script (short description):
% This script calls several other scripts that examine the model.
% Furthermore the converter is called to create the web resources.
%------------------------------------------------------------------------------------------------------------------
% Status (mark appropriate status with [x] below)
% [ ] Preliminary (experimental)
% [X] Baselined (not fully tested, but implementation finalized)
% [ ] Released (tested)
%------------------------------------------------------------------------------------------------------------------
% File name: CreateWebVisu.m
% File version: V2.0.0
% System:   
%   MATLAB Version: 9.3.0.713579 (R2017b)
%   Operating System: Microsoft Windows 7 Enterprise  Version 6.1 (Build 7601: Service Pack 1)
%	Java Version: Java 1.8.0_121-b13 with Oracle Corporation Java HotSpot(TM) 64-Bit Server VM mixed mode
%------------------------------------------------------------------------------------------------------------------
% MATLAB                                                Version 9.3         (R2017b)
% Simulink                                              Version 9.0         (R2017b)
% Control System Toolbox                                Version 10.3        (R2017b)
% Embedded Coder                                        Version 6.13        (R2017b)
% MATLAB Coder                                          Version 3.4         (R2017b)
% OPC Toolbox                                           Version 4.0.4       (R2017b)
% SIMATIC Target 1500S for Simulink                     Version 2.0.0.0     (V2.0)  
% Simulink Coder                                        Version 8.13        (R2017b)
% Simulink PLC Coder                                    Version 2.4         (R2017b)
% Stateflow                                             Version 9.0         (R2017b)
%------------------------------------------------------------------------------------------------------------------
% Restrictions, known limitations:
%   S7-1505S Software Controller V2.5
%   S7-1518 ODK V2.5
%
%   Simulink:
%       - (...)
%------------------------------------------------------------------------------------------------------------------
% Requirements, prerequisites, external resources used:
%   Same or equivalent system like system description.
%------------------------------------------------------------------------------------------------------------------
% Change log table (latest change is at the bottom of the list):
% Version  Date        Expert in charge     Changes applied
% V2.0.0   2018-05-25  APC Koeln (DJ)       Update to Target V2.0 
%                                           and ODK V2.5
% V1.0.1   2018-03-23  APC Koeln (DJ)		Change Path for ODK 2.5 and Target 2.0
%											Change deleting routine
% V1.0	   2017-09-27  APC Koeln (DJ)       First Release
% V0.3     2017-08-25  APC Koeln (DJ)       Add create JSON Files
% V0.2     2017-08-15  APC Koeln (DJ)       Integrate the SWV_Converter.exe and delete tmp files
% V0.1     2017-08-09  APC Koeln (DJ)       Add get_ModelReflection at Step 9 and primaly checks in 
%                                           Step 1.
%                                           First primarily Version of Matlab Interface.
%
% V0.0.4   2017-08-08  APC Koeln (DJ)       Add Step 8 Scope Script
%
% V0.0.3   2017-08-07  APC Koeln (DJ)       Add Step 5 - 7 and struct the scripts.
%
% V0.0.2   2017-08-03  APC Koeln (DJ)       Add TPS, SVGs, WSP, MWSP
%
% V0.0.1   2017-08-02  APC Koeln (DJ)       First develop
%------------------------------------------------------------------------------------------------------------------


%% CreateWebVisu(..)
%   param:  ModelName       - Name of the simulink model.

function CreateWebVisu(ModelName)

    %% Properties
        CheckModelExist = false;
		ErrorCode = 0;
        
    %% Start Info Text
    fprintf(['*********************************************\n', ...
             '* SIEMENS Simulink Web Visu Generator       *\n', ...
             '* Version V2.0.0                            *\n', ...
             '* SIEMENS AG                                *\n', ...
             '* RC-DE PD CSO 1 SD3 2                      *\n', ...
             '* � Copyright 2018. All Rights Reserved     *\n', ...
             '*-------------------------------------------*\n', ...
             '* This script analyzes your model and       *\n', ...
             '* creates the corresponding web resources.  *\n', ...
             '* Your model is created with the            *\n', ...
             '* Target1500S. Please note that your model  *\n', ...
             '* complies with the design guidelines.      *\n', ...
             '* (see manual)                              *\n', ...
             '*                                           *\n', ...
             '*********************************************\n', ...
             ' Create WebVisu for: ',ModelName,'\n\n\n', ... 
             ]);

    %% Check Modell
    try
        
        % exist simulink model
        result_exist = exist(ModelName);
        if result_exist == 4 
            CheckModelExist = true;
            fprintf('check model exists [ok]\n\n');
            fprintf('Create using files\n');
            ErrorCode = system('SWV_Converter.exe -createScripts');
        else
           fprintf('check model exists [failed]\n');
           CheckModelExist = false;
           fprintf(['CreateWebVisu can not find the simulink modell.\n', ...
                   '(1) Please check the modelname. \n', ...
                   '(2) The location should be the directory where the \n', ...
                   '    scripts, modelfile and the target output is.\n', ...
                   '\n end of generation \n']);
           % return
        end

        % search for FCN blocks
        disp('Do some previous checks [start]');
        load_system(ModelName);
        FcnBlocks = find_system(ModelName,'BlockType','Fcn');
        if length(FcnBlocks) > 0
            fprintf(['Attention!!\n', ...
                        'The Web Visu do not support Fcn Blocks \n', ...
                        'with Parameters in the Expression!']);
        end
        
        % check modell end
        fprintf('Do some previous checks [done]\n\n');
        
    catch ME
        %% Deactivate Lines
        warning off backtrace;
        
        %% Exception Handling
        warning('Unknown Error!');
        disp('[previous checks]: Error during CheckUp Modell.');
        disp('[previous checks]: Matlab Errorcode:');
        disp(ME);
        errorCode = ME;
        
        %% activate Lines
        warning on backtrace;
        
         return;
    end
    
    %% Extract InternalSignals
    try 
        if ErrorCode == 0
            if CheckModelExist
                result_find_script = exist('get_internalSignals');
                if  result_find_script == 2
                    fprintf('Extract TestPointedSignals [start]\n');
                    get_internalSignals(ModelName);
                    fprintf('Extract TestPointedSignals [done]\n\n');
                else
                    fprintf('Extract TestPointedSignals [failed]\n');
                    fprintf(['CreateWebVisu can not find the get_internalSignals.m script.\n', ...
                       '(1) Please check the location.\n', ...
                       '\n end of generation \n']);
                    return
                end
            end
        end  
        
        
    catch ME
        %% Deactivate Lines
        warning off backtrace;

        %% Exception Handling
        warning('Unknown Error!');
        disp('[get_internalSignals]: Error during extract internal signals.');
        disp('[get_internalSignals]: Matlab Errorcode:');
        disp(ME);
        errorCode = ME;

        %% activate Lines
        warning on backtrace;

         return;
    end
    
    %% Create SVG Graphics
    try 
        if ErrorCode == 0
            if CheckModelExist
                result_find_script = exist('SvgCreator');
                if  result_find_script == 2
                    fprintf('Create SVG Graphics [start]\n');

                    obj = SvgCreator(ModelName);
                    mainSvg = obj.createSvg(pwd);
                    disp(['Generated SVG file at:' mainSvg]);

                    fprintf('Create SVG Graphics [done]\n\n');
                else
                    fprintf('Create SVG Graphics  [failed]\n');
                    fprintf(['CreateWebVisu can not find the SvgCreator.m script.\n', ...
                       '(1) Please check the location.\n', ...
                       '\n end of generation \n']);
                    return
                end
            end
        end
    catch ME
        %% Deactivate Lines
        warning off backtrace;

        %% Exception Handling
        warning('Unknown Error!');
        disp('[SvgCreator]: Error during create SVG graphics.');
        disp('[SvgCreator]: See manual desgin guidelines.');
        disp('[SvgCreator]: Matlab Errorcode:');
        disp(ME);
        errorCode = ME;

        %% activate Lines
        warning on backtrace;

         return;
    end
    
	%% Extract SpaceParameters
    try 
        if ErrorCode == 0
            if CheckModelExist
                result_find_script = exist('get_SpaceParameters');
                if  result_find_script == 2
                    fprintf('Extract Space Variables [start]\n');
                    get_SpaceParameters(ModelName);
                    fprintf('Extract Space Variables [done]\n\n');
                else
                    fprintf('Extract Space Variables [failed]\n');
                    fprintf(['CreateWebVisu can not find the get_SpaceParameters.m script.\n', ...
                       '(1) Please check the location.\n', ...
                       '\n end of generation \n']);
                    return
                end
            end
        end
    catch ME
        %% Deactivate Lines
        warning off backtrace;

        %% Exception Handling
        warning('Unknown Error!');
        disp('[get_SpaceParameters]: Error during get parameters from Workspace and/or Modellworkspace.');
        disp('[get_SpaceParameters]: Matlab Errorcode:');
        disp(ME);
        errorCode = ME;

        %% activate Lines
        warning on backtrace;

         return;
    end
    
    %% Extract Inports
    try 
        if ErrorCode == 0
            if CheckModelExist
                result_find_script = exist('get_Inports');
                if  result_find_script == 2
                    fprintf('Extract Inports [start]\n');
                    get_Inports(ModelName);
                    fprintf('Extract Inports [done]\n\n');
                else
                    fprintf('Extract Inports [failed]\n');
                    fprintf(['CreateWebVisu can not find the get_Inports.m script.\n', ...
                       '(1) Please check the location.\n', ...
                       '\n end of generation \n']);
                    return
                end
            end
        end
    catch ME
        %% Deactivate Lines
        warning off backtrace;

        %% Exception Handling
        warning('Unknown Error!');
        disp('[get_Inports]: Error during read inports.');
        disp('[get_Inports]: Matlab Errorcode:');
        disp(ME);
        errorCode = ME;

        %% activate Lines
        warning on backtrace;

         return;
    end
    
    %% Extract Outports
    try 
        if ErrorCode == 0
            if CheckModelExist
                result_find_script = exist('get_Outports');
                if  result_find_script == 2
                    fprintf('Extract Outports [start]\n');
                    get_Outports(ModelName);
                    fprintf('Extract Outports [done]\n\n');
                else
                    fprintf('Extract Outports [failed]\n');
                    fprintf(['CreateWebVisu can not find the get_Outports.m script.\n', ...
                       '(1) Please check the location.\n', ...
                       '\n end of generation \n']);
                    return
                end
            end
        end
    catch ME
        %% Deactivate Lines
        warning off backtrace;

        %% Exception Handling
        warning('Unknown Error!');
        disp('[get_Outports]: Error during read outports.');
        disp('[get_Outports]: Matlab Errorcode:');
        disp(ME);
        errorCode = ME;

        %% activate Lines
        warning on backtrace;

         return;
    end
    
    %% Extract Scopes
    try 
        if ErrorCode == 0
            if CheckModelExist
                result_find_script = exist('get_Scopes');
                if  result_find_script == 2
                    fprintf('Extract Scopes [start]\n');
                    get_Scopes(ModelName);
                    fprintf('Extract Scopes [done]\n\n');
                else
                    fprintf('Extract Scopes [failed]\n');
                    fprintf(['CreateWebVisu can not find the get_Scopes.m script.\n', ...
                       '(1) Please check the location.\n', ...
                       '\n end of generation \n']);
                    return
                end
            end
        end       
    catch ME
        %% Deactivate Lines
        warning off backtrace;

        %% Exception Handling
        warning('Unknown Error!');
        disp('[get_Scopes]: Error during read and get Scopes.');
        disp('[get_Scopes]: Matlab Errorcode:');
        disp(ME);
        errorCode = ME;

        %% activate Lines
        warning on backtrace;

         return;
    end

    %% Extract Model Struct
    try 
        if ErrorCode == 0
            if CheckModelExist
                result_find_script = exist('get_ModelReflection');
                if  result_find_script == 2
                    fprintf('Extract model struct [start]\n');
                    get_ModelReflection(ModelName);
                    fprintf('Extract model struct [done]\n\n');
                else
                    fprintf('Extract model struct [failed]\n');
                    fprintf(['CreateWebVisu can not find the get_ModelReflection.m script.\n', ...
                       '(1) Please check the location.\n', ...
                       '\n end of generation \n']);
                    return
                end
            end
        end       
    catch ME
        %% Deactivate Lines
        warning off backtrace;

        %% Exception Handling
        warning('Unknown Error!');
        disp('[get_ModelReflection]: Error during get model structure.');
        disp('[get_ModelReflection]: Matlab Errorcode:');
        disp(ME);
        errorCode = ME;

        %% activate Lines
        warning on backtrace;

         return;
    end

	%% Build ODK solution
    try 
         if ErrorCode == 0
            fprintf('build the ODK project [start]\n');

            rtwbuild(ModelName);

            fprintf('build the ODK project [done]\n');
         end       
    catch ME
        %% Deactivate Lines
        warning off backtrace;

        %% Exception Handling
        warning('Unknown Error!');
        disp('[ODK Build]: Error during build model.');
        disp('[ODK Build]: Matlab Errorcode:');
        disp(ME);
        errorCode = ME;

        %% activate Lines
        warning on backtrace;

         return;
    end

	%% Edit ODK Projekt (unused)
    % if ErrorCode == 0
	%	fprintf('Edit ODK project [start]\n');
	%	ErrorCode = system('SWV_Converter.exe -modifiedODK1500SProject');
	%	fprintf('Edit ODK project [done]\n\n');
    % end

    %% Create JSON Files
    try 
        if ErrorCode == 0
            fprintf('Create JSON Files [start]\n');
            ErrorCode = system('SWV_Converter.exe -createJsonFiles');
            fprintf('Create JSON Files [done]\n\n');
        end 
    catch ME
        %% Deactivate Lines
        warning off backtrace;

        %% Exception Handling
        warning('Unknown Error!');
        disp('[createJsonFiles]: Error during create web resources (JSON files)');
        disp('[createJsonFiles]: Matlab Errorcode:');
        disp(ME);
        errorCode = ME;

        %% activate Lines
        warning on backtrace;

         return;
    end

	%% Modified SVG Files
    try 
        if ErrorCode == 0
            fprintf('Edit SVG Files [start]\n');
            ErrorCode = system('SWV_Converter.exe -modifiedSvgGraphics');
            fprintf('Edit SVG Files [done]\n\n');
        end       
    catch ME
        %% Deactivate Lines
        warning off backtrace;

        %% Exception Handling
        warning('Unknown Error!');
        disp('[modifiedSvgGraphics]: Error during modified svg files.');
        disp('[modifiedSvgGraphics]: Matlab Errorcode:');
        disp(ME);
        errorCode = ME;

        %% activate Lines
        warning on backtrace;

         return;
    end

	%% Create Website
    try 
       if ErrorCode == 0
            fprintf('Create Website [start]\n');
            ErrorCode = system('SWV_Converter.exe -createWebsite');
            fprintf('Create Website [done]\n\n');
        end
    catch ME
        %% Deactivate Lines
        warning off backtrace;

        %% Exception Handling
        warning('Unknown Error!');
        disp('[createWebsite]: Error during create website');
        disp('[createWebsite]: Matlab Errorcode:');
        disp(ME);
        errorCode = ME;

        %% activate Lines
        warning on backtrace;

         return;
    end

	%% Create Interface DB
    try 
       if ErrorCode == 0
            fprintf('Create Interface DB [start]\n');
            ErrorCode = system('SWV_Converter.exe -createInterfaceDB');
            fprintf('Create Interface DB [done]\n\n');
        end
    catch ME
        %% Deactivate Lines
        warning off backtrace;

        %% Exception Handling
        warning('Unknown Error!');
        disp('[createInterfaceDB]: Error during create Interface DB');
        disp('[createInterfaceDB]: Matlab Errorcode:');
        disp(ME);
        errorCode = ME;

        %% activate Lines
        warning on backtrace;

         return;
    end

	%% Rebuild ODK solution (unused)
	% if ErrorCode == 0
	%	fprintf('Rebuild the ODK project with headless build from eclipse [start]\n');
	%	Old_Dir = pwd;
    %	cd 'C:\Program Files (x86)\Siemens\Automation\ODK1500S\V2.5\eclipse';
	%	%command = ['eclipse.exe -nosplash -application org.eclipse.cdt.managedbuilder.core.headlessbuild -import ',Old_Dir,'\',ModelName,'_Target_1500S_V1_0_grt_Output\',ModelName,'_ODK -data C:\ProgramData\Siemens\Automation\ODK1500S\V2.0\eclipse\V2.0\workspace\ -cleanBuild ',ModelName,'_ODK/release_so'];
	%	command = ['eclipse.exe -nosplash -application org.eclipse.cdt.managedbuilder.core.headlessbuild -import ',Old_Dir,'\',ModelName,'_Target_1500S_V2_0_grt_Output\',ModelName,'_ODK -cleanBuild ',ModelName,'_ODK/release_so'];
	%	system(command);
	%	cd(Old_Dir);
	%	fprintf('Rebuild the ODK project with headless build from eclipse [done]\n');
    % end
    
    %% Delete Scripts
    try 
        fprintf('Delete all temp files [start]\n');
		system('SWV_Converter.exe -deleteScripts');

		result_exist = exist(ModelName);
		
		if exist('IN.xml') == 2
			delete 'IN.xml';	
		end

		if exist('OUT.xml') == 2
			delete 'OUT.xml';	
		end

		if exist('SCOPES.xml') == 2
			delete 'SCOPES.xml';	
		end

		if exist('TPS.xml') == 2
			delete 'TPS.xml';	
		end

		if exist('WSP.xml') == 2
			delete 'WSP.xml';	
		end

		if exist('MODEL.xml') == 2
			delete 'MODEL.xml';	
		end

		if exist('MWSP.xml') == 2
			delete 'MWSP.xml';	
		end

		fprintf('Delete all temp files [done]\n');
    catch ME
        %% Deactivate Lines
        warning off backtrace;

        %% Exception Handling
        warning('Unknown Error!');
        disp('[delete temp]: Error during delete temp files.');
        disp('[delete temp]: Matlab Errorcode:');
        disp(ME);
        errorCode = ME;

        %% activate Lines
        warning on backtrace;

         return;
    end

	%% Show Error code
    if ErrorCode > 0 
        disp('Finished with Error Code = ');
        disp(ErrorCode);
    end
    
end