#include "../../definitions.h"
#include "../exceptions/AwesomeNotificationException.h"
#include "../models/AbstractModel.h"
#include "../../utils/StringUtils.h"

#include <string>
#include <vector>
#include <optional>

template <class T>
class SharedManager { // AbstractModel
 private:
    std::string className;

    const static inline std::string TAG = "SharedManager";

    std::string reference;
    std::string hashedReference = "default";

    /*
    SharedPreferences GetSharedInstance() {

        auto preferences = context.getSharedPreferences(
                context.getPackageName() + "." + hashedReference,
                Context.MODE_PRIVATE
        );

        if(preferences == null){
            throw AwesomeNotificationException("SharedPreferences.getSharedPreferences return null");
        }

        return preferences;
    }
    */

    std::string GenerateSharedKey(std::string tag, std::string referenceKey) {
        return tag + '_' + referenceKey;
    }

    /*
    static void CommitAsync(const std::string reference, SharedPreferences::Editor editor) {
        editor.Commit();
        new AsyncTask<Void, Void, bool>() {
            @Override
            protected bool doInBackground(Void... voids) {
                return editor.commit();
            }

            @Override
            protected void onPostExecute(bool value) {
                if(!value){
                    Log.d(reference,"shared data could not be saved");
                }
            }
        }.execute();
    }*/

 public:

    SharedManager(std::string fileIdentifier, std::string className) {
        this->className = className;
        this->reference = Definitions::SHARED_MANAGER + "." + fileIdentifier + "." + className;
        try {
            this->hashedReference = StringUtils::DigestString(reference);
            //Log.d(TAG, fileIdentifier+": file initialized = "+ hashedReference);
        } catch (std::exception e) {
            this->hashedReference = reference;
            //Log.e(TAG, "SharedManager could not be correctly initialized: "+ e.getMessage());
            //e.printStackTrace();
        }
    }

    void Commit() {
        try {

            //auto shared = GetSharedInstance();
            //SharedPreferences::Editor editor = shared.Edit();

            //CommitAsync(reference, editor);

        } catch (std::exception e){
            //e.printStackTrace();
            //Log.e(TAG, e.toString());
        }
    }

    std::vector<T> GetAllObjects(std::string tag) {
        std::vector<T> returnedList;
        try {
            /*
            auto shared = GetSharedInstance();

            auto tempMap = shared.GetAll();

            if(tempMap) {
                for (auto entry : tempMap) {
                    std::string key = entry.GetKey();
                    auto value = entry.GetValue();

                    if(key.StartsWith(tag) && value instanceof std::string){
                        T object;
                        returnedList.push_back((T) object.FromJson((std::string) value));
                    }
                }
            }
            */
        } catch (std::exception e){
            //e.printStackTrace();
            //Log.e(TAG, e.toString());
        }

        return returnedList;
    }

    std::optional<T> Get(std::string tag, std::string referenceKey) {

        try {
            /*
            auto shared = GetSharedInstance();

            std::string sharedKey = GenerateSharedKey(tag, referenceKey);
            std::string json = shared.GetString(sharedKey, nullptr);

            T returnedObject{};
            if (!StringUtils::IsNullOrEmpty(json)) {
                T genericModel;

                AbstractModel parsedModel = genericModel.FromJson(json);
                if(parsedModel) {
                    returnedObject = (T) parsedModel;
                }
            }

            return returnedObject;
            */

        } catch (AwesomeNotificationException e) {
            //e.printStackTrace();
            //Log.e(TAG, e.toString());
        } catch (std::exception e) {
            //e.printStackTrace();
        }

        return {};
    }

    bool Set(std::string tag, std::string referenceKey, T data) {

        try {

            /*
            auto shared = GetSharedInstance();

            std::string sharedKey = GenerateSharedKey(tag, referenceKey);

            std::string json = data.ToJson();

            SharedPreferences::Editor editor = shared.Edit();

            editor.PutString(sharedKey, json);
            editor.Apply();

            return true;
            */

        } catch (AwesomeNotificationException e) {
            //e.printStackTrace();
            //Log.e(TAG, e.toString());
        }

        return false;
    }

    bool Remove(std::string tag, std::string referenceKey) {

        try {
            /*
            auto shared = GetSharedInstance();

            std::string sharedKey = GenerateSharedKey(tag, referenceKey);

            SharedPreferences::Editor editor = shared.Edit();
            editor.Remove(sharedKey);

            editor.Apply();

            return true;
            */

        } catch (AwesomeNotificationException e) {
            //e.printStackTrace();
            //Log.e(TAG, e.toString());
        }

        return false;
    }

};
